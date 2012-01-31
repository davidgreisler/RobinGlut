#include "game.hpp"
#include "level.hpp"
#include "player.hpp"
#include "levels/level1.hpp"
#include "levels/level2.hpp"
#include "levels/level3.hpp"

namespace robinglut
{
	/**
	 * Creates a new game object using the given renderer.
	 * 
         * @param renderer Renderer to use.
         */
	game::game(glut_renderer& renderer)
		: renderer(renderer), current_level_index(0), current_level(0)
	{
		
	}
	
	/**
	 * Frees all used resources.
         */
	game::~game()
	{
		
	}
	
	/**
	 * Starts the next level.
	 * 
         * @param int ignored.
         */
	void game::next_level(int)
	{
		// @todo The old level is not freed here. Do this in a level 
		// loader?!
                // Man sollte besser die levels in Liste speichern als in Dateien..
		
		switch (this->current_level_index)
		{
			case 1: this->start_level(new level_2(this->player));
			        break;
			case 2: this->start_level(new level_3(this->player));
			        break;
			case 3: this->game_over_event(this->player->get_score());
			        break;
		}
	}
	
	/**
	 * Starts the given level.
	 * 
         * @param level The level to start.
         */
	template<class L>
	void game::start_level(L* level)
	{
		this->current_level_index++;
		this->player->set_current_level(this->current_level_index);
		
		this->current_level = level;
		this->renderer.set_current_scene(this->current_level);
		this->current_level->finished_event += event::event_listener(this, &game::next_level);
	}
	
	/**
	 * Starts a new game.
         */
	void game::start()
	{
		this->player = new robinglut::player(10);
		
		this->current_level_index = 0;
		this->start_level(new level_1(this->player));
	}
	
}
