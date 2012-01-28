#include <GL/glut.h>

#include "glut_renderer.hpp"
#include "scene.hpp"

namespace robinglut
{
	
	/**
	 * The renderer which is registered to glut, respectively is receiving
	 * GLUT events (this is a workaround because GLUT's callbacks do not
	 * support methods).
         */
	static glut_renderer* registered_renderer;
	
	/**
	 * Creates a new renderer object and initializes it (using glut).
	 */
	glut_renderer::glut_renderer(int argc, char** argv)
		: current_scene(0)
	{
		// Initialize GLUT.

		glutInit(&argc, argv);

		// Display mode for the window to create.
		// GLUT_DOUBLE: Double buffering.
		// GLUT_RGB: RGBA mode.
		// GLUT_DEPTH: Use a depth buffer (objects which are nearer to the camera 
		//             overlap ones that are behind them).

		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

		// Size of the window.

		glutInitWindowSize(1024, 768);

		// Position of the window on the screen.

		glutInitWindowPosition(0, 0);

		// Create the window and use the argument as title.

		glutCreateWindow("Robin Glut");

		this->initialize();
	}

	/**
	 * Frees all used resources.
	 */
	glut_renderer::~glut_renderer()
	{

	}

	/**
	 * Initializes lighting.
         */
	void glut_renderer::initialize_lighting()
	{
		// Activate lighting.

		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		
		
		
		GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat mat_shininess[] = {50.0};

		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

		// Light source 0.
		
		GLfloat light_position0[] = {0.0, 50, 0, 1};
		GLfloat red[] = {255, 255, 255, 1};

		glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
		
		// Activate light sources.

		glEnable(GL_LIGHT0);
		//glEnable(GL_LIGHT1);

		// Activate depth testing, so that depth information is stored in the depth
		// buffer. This way, pixels of objects that are closer to the viewpoint
		// replace/overwrite pixels that are farther away.

		glEnable(GL_DEPTH_TEST);
		
	}

	/**
	 * Initializes GLUT.
         */
	void glut_renderer::initialize()
	{
		this->initialize_lighting();
		
		// Specify the colors used to clear the color buffers.

		glClearColor(0.0, 0.0, 0.0, 0.0);

		// Activate smooth shading (the color of each pixel of a polygon is 
		// calculated individually, unlike GL_FLAT where all pixels of a polygon
		// have the same color).

		glShadeModel(GL_SMOOTH);

		// Tells OpenGL how pixels are stored in memory. The following call says
		// that there is 1 byte for each color (red, green, blue).

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Set some texture filtering properties.

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	/**
	 * Registers the GLUT callbacks and starts the main loop.
         */
	void glut_renderer::register_renderer()
	{
		registered_renderer = this;
		
		// Set callback function that is called when the window contents are 
		// repainted.

		glutDisplayFunc(&glut_renderer::display);

		// Set callback function that is called when the window is resized.

		glutReshapeFunc(&glut_renderer::reshape);

		// Set callback function that is called when a key is pressed.

		glutKeyboardFunc(&glut_renderer::on_keypress);
		
		// Mouse click callback.
		
		glutMouseFunc(&glut_renderer::on_mouse);
		
		// Motion callback.
		
		glutMotionFunc(&glut_renderer::on_active_motion);

		// Start main loop.

		glutMainLoop();
	}

	/**
	 * Sets the currently displayed scene. Emits a redisplay event.
	 * 
         * @param scene The new scene.
         */
	void glut_renderer::set_current_scene(scene* scene)
	{
		this->current_scene = scene;
		this->redisplay();
	}
	
	/**
	 * Returns the currently displayed scene.
	 * 
         * @return The current scene.
         */
	scene* const glut_renderer::get_current_scene() const
	{
		return this->current_scene;
	}
	
	/**
	 * Emits a GLUT post redisplay event (redisplays the scene).
         */
	void glut_renderer::redisplay()
	{
		glutPostRedisplay();
	}

	/**
	 * Displays the current scene.
         */
	void glut_renderer::display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glScalef(1.0, 1.0, 1.0);
		gluLookAt(0, 10, 0, 1, 10, 0, 0.0, 1.0, 0.0);

		if (0 != registered_renderer->get_current_scene())
		{
			registered_renderer->get_current_scene()->display();
		}
		
		glFlush();
		glutSwapBuffers();
	}

	/**
	 * Is called when the window size changes.
	 * 
	 * @param width New width.
	 * @param height New height.
	 */
	void glut_renderer::reshape(int width, int height)
	{
		glViewport(0, 0, (GLsizei) width, (GLsizei) height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		
		if (0 != registered_renderer->get_current_scene())
		{
			registered_renderer->get_current_scene()->reshape(width, height);
		}
	}

	/**
	 * Keypress handler, performs actions depending on which key was pressed.
	 * 
	 * @param key The key that was pressed.
	 * @param x Ignored.
	 * @param y Ignored.
	 */
	void glut_renderer::on_keypress(unsigned char key, int x, int y)
	{
		if (0 != registered_renderer->get_current_scene())
		{
			registered_renderer->get_current_scene()->on_keypress(key, x, y);
		}
	}
	
	/**
	 * Mouse button handler.
	 * 
         * @param button Which button was pressed/released.
         * @param state Whether it was pressed or released.
         * @param x X position.
         * @param y Y position.
         */
	void glut_renderer::on_mouse(int button, int state, int x, int y)
	{
		if (0 != registered_renderer->get_current_scene())
		{
			registered_renderer->get_current_scene()->on_mouse(button, state, x, y);
		}
	}
	
	/**
	 * Mouse movement handler (called when the mouse is moved).
	 * 
         * @param x X position.
         * @param y Y position.
         */
	void glut_renderer::on_active_motion(int x, int y)
	{
		if (0 != registered_renderer->get_current_scene())
		{
			registered_renderer->get_current_scene()->on_active_motion(x, y);
		}
	}
}
