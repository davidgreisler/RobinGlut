#include <cstdlib>

#include "robin_glut.hpp"
#include "menu.hpp"
#include "game.hpp"

namespace robinglut
{
	/**
	 * Creates a new robin glut object.
	 * 
	 * @param argc Pointer to argc from main.
	 * @param argv Pointer to argv from main.
	 */
	robin_glut::robin_glut(int argc, char** argv)
		: renderer(argc, argv), game(renderer)
	{
		this->menu.option_selected_event += event::event_listener(this, &robin_glut::menu_selection);
		this->game.game_over_event += event::event_listener(this, &robin_glut::game_over);
	}

	/**
	 * Frees all used resources.
	 */
	robin_glut::~robin_glut()
	{

	}
	
	/**
	 * Called when the game is over, shows the menu again.
	 * 
         * @param int ignored.
         */
	void robin_glut::game_over(int)
	{
		this->renderer.set_current_scene(&this->menu);
	}
	
	/**
	 * Called when an option in the menu is selected.
	 * 
         * @param what Which option is selected.
         */
	void robin_glut::menu_selection(int what)
	{
		switch (what)
		{
			case 1: this->start_new_game(); break;
			case 2: break;
			case 3: break;
			case 4: this->quit(); break;
		}
	}
	
	/**
	 * Starts a new game.
         */
	void robin_glut::start_new_game()
	{
		this->game.start();
	}
	
	/**
	 * Ends program execution.
	 */
	void robin_glut::quit()
	{
		std::exit(0);
	}

	/**
	 * Runs the application (main loop).
	 * 
	 * @return Returns 0.
	 */
	int robin_glut::run()
	{
		this->renderer.set_current_scene(&this->menu);
		this->renderer.register_renderer();
		
		return 0;
	}
	
	/**
	 * Emits a redisplay event every 1/25 seconds.
	 * 
         * @param ignored.
         */
	void robin_glut::refresh(int)
	{
		glut_renderer::get_registered_renderer()->redisplay();
		glut_renderer::get_registered_renderer()->set_timeout(25, &robin_glut::refresh, 0);
	}
}
