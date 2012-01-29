#ifndef LEVEL_HPP
#define	LEVEL_HPP

#include <vector>

#include "scene.hpp"
#include "arrow.hpp"
#include "target.hpp"
#include "bow.hpp"
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
		 * The texture for the butt.
		 */
		GLuint butt_texture;
		
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
		 * The bow used to fire arrows.
		 */
		robinglut::bow* bow;
                /*
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
		
                /*
                 * Current Arrow
                 */
                
                arrow* last_fired_arrow;
                
                /**
		 * The targets
		 */
		std::vector<robinglut::target*> targets;
                
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
		
	public:
		level();
		
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

