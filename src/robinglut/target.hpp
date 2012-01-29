#ifndef TARGET_HPP
#define	TARGET_HPP

#include <GL/gl.h>

#include "../event/event.hpp"

namespace robinglut
{
	/**
	 * Draws a butt at the given position.
	 */
	class target
	{
	private:
		/**
		 * The width of the butt.
		 */
		float width;
		
		/**
		 * The height of the butt.
		 */
		float height;
		
		/**
		 * The position on the x axis.
		 */
		float x;
		
		/**
		 * The position on the y axis.
		 */
		float y;
		
		/**
		 * The position on the z axis.
		 */
		float z;
		
		/**
		 * The texture of the butt.
		 */
		GLuint texture;
		
	public:
		target(float x, float y, float z, float width, float height, 
		       GLuint texture);
		target(const target& orig);
		virtual ~target();
		
		/**
		 * This event is emitted when the target is scored by an arrow.
		 * 
		 * Ignore the integer.
                 */
		event::event<int> got_scored;
		
		float get_x() const;
		float get_y() const;
		float get_z() const;
		
		float get_width() const;
		float get_height() const;
		
		void score();
		
		void display();
	};

}

#endif	/* TARGET_HPP */
