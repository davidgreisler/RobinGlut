#ifndef USER_INTERFACE_HPP
#define	USER_INTERFACE_HPP

#include <GL/gl.h>

#include "player.hpp"

namespace robinglut
{
	class arrow;
	
	/**
	 * The user interface while playing (displays level/points/remaining 
	 * arrows/etc.).
	 */
	class user_interface
	{
	private:
		/**
		 * The background image.
		 */
		GLuint background_image;
                
		
		/**
		 * Reference to the player, used to retrieve force/speed
		 * and remaining arrows.
		 */
		robinglut::player& player;
		
		void print_text(float x, float y, float z, const char* text, float r, float g, float b, float a);
                void draw_crosshair_force();
		void draw_background();
		void draw_counts();
	public:
		user_interface(robinglut::player& player);
		
		void display();
	};
}

#endif	/* USER_INTERFACE_HPP */

