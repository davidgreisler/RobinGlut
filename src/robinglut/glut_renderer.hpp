#ifndef RENDERER_HPP
#define	RENDERER_HPP

namespace robinglut
{
	class scene;
	
	/**
	 * GLUT renderer, responsible for GLUT initialization and GLUT event 
	 * disposal.
	 * 
	 * @author David Greisler <kontakt@davidgreisler.de>
	 */
	class glut_renderer
	{
	private:
		/**
		 * Pointer to the currently displayed scene.
		 */
		scene* current_scene;

		void initialize_lighting();
		void initialize();
	public:
		glut_renderer(int argc, char** argv);
		~glut_renderer();

		void register_renderer();

		void set_current_scene(scene* scene);
		scene* const get_current_scene() const;
		
		void redisplay();

		static void display();
		static void reshape(int width, int height);
		static void on_keypress(unsigned char key, int x, int y);
		static void on_mouse(int button, int state, int x, int y);
		static void on_active_motion(int x, int y);
	};
}

#endif	/* RENDERER_HPP */

