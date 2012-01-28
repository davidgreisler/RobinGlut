#ifndef ROBINGLUT_HPP
#define	ROBINGLUT_HPP

#include "glut_renderer.hpp"
#include "menu.hpp"
#include "game.hpp"

namespace robinglut
{
	/**
	 * Main application class, contains application logic and controls program flow.
	 * 
	 * @author David Greisler <kontakt@davidgreisler.de>
	 */
	class robin_glut
	{
	private:
		/**
		 * GLUT renderer.
		 */
		glut_renderer renderer;
		
		/**
		 * The menu.
		 */
		robinglut::menu menu;
		
		/**
		 * Game engine.
		 */
		robinglut::game game;

		/**
		 * Main loop condition.
		 */
		bool running;
		
		void game_over(int);
		void menu_selection(int what);
		void start_new_game();
		void quit();
	public:
		robin_glut(int argc, char** argv);
		~robin_glut();

		int run();
	};
}

#endif	/* ROBINGLUT_HPP */

