#ifndef LEVEL_HPP
#define	LEVEL_HPP

#include <vector>

#include "scene.hpp"
#include "arrow.hpp"
#include "target.hpp"
#include "player.hpp"
#include "heightmap.hpp"
#include "user_interface.hpp"
#include "../event/event.hpp"

namespace robinglut
{
	
	/**
	 * A game level.
         */
	class level : public scene
	{
	private:
		/**
		 * The game player
		 */
		robinglut::player* player;
		
		/**
		 * The texture used for the ground.
		 */
		GLuint ground_texture;
		
		/**
		 * Surrounding area: left texture.
		 */
		GLuint area_left_texture;
		
		/**
		 * Surrounding area: right texture.
		 */
		GLuint area_right_texture;
		
		/**
		 * Surrounding area: center texture.
		 */
		GLuint area_center_texture;
		
		/**
		 * The user interface.
		 */
		user_interface* ui;
		
                /**
                 * Heightmap terrain
                 */
                robinglut::heightmap* map;
                               
		/**
		 * The arrows fired by the player.
		 */
		std::vector<robinglut::arrow*> arrows;
		
		/**
		 * Whether the left/middle/right mouse button is pressed ATM.
		 */
		bool button_pressed[3];
		
                /**
		 * The last arrow that got fired.
                 */
                arrow* last_fired_arrow;
                
		float anglex;
		float angley;
		float anglez;
		int lastx;
		int lasty;
		
                void draw_targets();
		void draw_arrows();
		void draw_ground();
		void draw_sky();
		void draw_surrounding_area();
                void check_collision();
		void increase_score(target* hit_target);
		
		void start_drawing();
		void fire_arrow();
		
	protected:
		/**
		 * The texture for the butt.
		 */
		GLuint butt_texture;
		
		/**
		 * The targets
		 */
		std::vector<robinglut::target*> targets;
		
		void initialize();
		
	public:
		level(robinglut::player* game_player);
		
		/**
		 * Event that is emitted when the level was finished.
		 * 
		 * This means the player either won or lost (no more arrows).
		 */
		event::event<int> finished_event;
		
		virtual void display();
		virtual void on_mouse(int button, int state, int x, int y);
		virtual void on_active_motion(int x, int y);
	};
}

#endif	/* LEVEL_HPP */

