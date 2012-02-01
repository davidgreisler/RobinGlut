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
                 
                /* 
                 * Is the target hitted?
                 */
                bool hitted;
                
                 /* 
                 * When > 0 the target is animated
                 */
                float range;
                
                /*
                 * reach the end of a range
                 */
                bool range_end;
                float range_min;
                float range_max;
		
	public:
		target(float x, float y, float z, float width, float height, 
		       GLuint texture);
		target(const target& orig);
		virtual ~target();
		
		/**
		 * This event is emitted when the target is scored by an arrow.
		 * 
		 * The first argument is this target.
                 */
		event::event<target*> got_scored;
		
		float get_x() const;
		float get_y() const;
		float get_z() const;
		
		float get_width() const;
		float get_height() const;
		
		void score();
		void display();
                
                bool get_hitted();
                void set_hitted();
                
                void set_animated(float range);
	};

}

#endif	/* TARGET_HPP */
