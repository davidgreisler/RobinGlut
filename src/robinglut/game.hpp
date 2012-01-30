#ifndef GAME_HPP
#define	GAME_HPP

#include "glut_renderer.hpp"
#include "../event/event.hpp"

namespace robinglut
{
	class player;
	class level;
	
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
		
		/**
		 * The player.
		 */
		robinglut::player* player;
		
		/**
		 * The current level (as number).
                 */
		int current_level_index;
		
		/**
		 * Pointer to the current level.
                 */
		level* current_level;
		
		void next_level(int);
		
		template<class L>
		void start_level(L* level);
	public:
		game(glut_renderer& renderer);
		~game();
		
		// ignore the int. @todo event w/o args.
		event::event<int> game_over_event;
		
		void start();
	};
}

#endif	/* GAME_HPP */

