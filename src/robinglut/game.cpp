#include "game.hpp"
#include "level.hpp"

namespace robinglut
{
	/**
	 * Creates a new game object using the given renderer.
	 * 
         * @param renderer Renderer to use.
         */
	game::game(glut_renderer& renderer)
		: renderer(renderer)
	{
		
	}
	
	/**
	 * Frees all used resources.
         */
	game::~game()
	{
		
	}
	
	/**
	 * Is called when a level is finished (loads next level).
	 * 
         * @param int ignored.
         */
	void game::finished_level(int)
	{
		this->game_over_event(123);
	}
	
	/**
	 * Starts a new game.
         */
	void game::start()
	{
		level* level1 = new level;
		this->renderer.set_current_scene(level1);
		level1->finished_event += event::event_listener(this, &game::finished_level);
	}
	
}
