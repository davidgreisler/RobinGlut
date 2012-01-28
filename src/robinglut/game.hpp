#ifndef GAME_HPP
#define	GAME_HPP

#include "glut_renderer.hpp"
#include "../event/event.hpp"

namespace robinglut
{
	/**
	 * The game engine, provides a method to start a new game, loads levels
	 * and then returns to the menu when the game is over.
	 */
	class game
	{
	private:
		/**
		 * The GLUT renderer.
		 */
		glut_renderer& renderer;
	public:
		game(glut_renderer& renderer);
		~game();
		
		// ignore the int. @todo event w/o args.
		event::event<int> game_over_event;
		
		void start();
		void finished_level(int);
	};
}

#endif	/* GAME_HPP */

