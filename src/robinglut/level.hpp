#ifndef LEVEL_HPP
#define	LEVEL_HPP

#include "scene.hpp"
#include "arrow.hpp"
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
		
		robinglut::arrow* arrow;
		user_interface* ui;
		float anglex;
		float angley;
		float anglez;
		int lastx;
		int lasty;
		unsigned char Buttons[3];
		
		void draw_butt(int x, int y, int z);
		void draw_ground();
		void draw_sky();
		void draw_surrounding_area();
		
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

