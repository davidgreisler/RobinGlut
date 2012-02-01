#ifndef MENU_HPP
#define	MENU_HPP

#include "GL/glut.h"

#include "scene.hpp"
#include "../event/event.hpp"

namespace robinglut
{
	/**
	 * The main menu.
	 * 
	 * @author David Greisler <kontakt@davidgreisler.de>
	 */
	class menu : public scene
	{
	private:
		GLuint title;
		
	public:
		menu();
		~menu();
		
		event::event<int> option_selected_event;

		virtual void display();
		//virtual void reshape(int width, int height);
		virtual void on_keypress(unsigned char key, int x, int y);
                virtual void on_mouse(int button, int state, int x, int y);
	};

}

#endif	/* MENU_HPP */

