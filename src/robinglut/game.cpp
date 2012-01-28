#include "game.hpp"
#include "level.hpp"

namespace robinglut
{
	game::game(glut_renderer& renderer)
		: renderer(renderer)
	{
		
	}
	
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
	
	void game::start()
	{
		level* level1 = new level;
		this->renderer.set_current_scene(level1);
		level1->finished_event += event::event_listener(this, &game::finished_level);
	}
	
}
