#ifndef SCENE_HPP
#define	SCENE_HPP

namespace robinglut
{
	/**
	 * A scene to display, contains the logic to display the screen's content.
	 *
	 * This class contains 3 methods which are called by the main class when the
	 * corresponding GL event occurs:
	 *
	 * * display() is called when the screen contents are repainted.
	 * * reshape() is called when the screen is resized.
	 * * onKeypress() is called when the user presses a key.
	 *
	 * @author David Greisler <kontakt@davidgreisler.de>
	 **/
	class scene
	{
	public:
		scene();
		~scene();

		virtual void display();
		virtual void reshape(int width, int height);
		virtual void on_keypress(unsigned char key, int x, int y);
		virtual void on_mouse(int button, int state, int x, int y);
		virtual void on_active_motion(int x, int y);
	};
}

#endif	/* SCENE_HPP */

