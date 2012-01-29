#ifndef ARROW_HPP
#define	ARROW_HPP

#include <vector>

#include "target.hpp"

namespace robinglut
{

	/**
	 * An arrow, fired by the player.
	 */
	class arrow
	{
	private:
		/**
		 * Current X position.
		 */
		float x; 
		
		/**
		 * Current Y position.
		 */
		float y;
		
		/**
		 * Current Z position.
		 */
		float z;
		
		/**
		 * X angle.
		 */
		float angle_x;
		
		/**
		 * Y angle.
		 */
		float angle_y;
                
		/**
		 * Time when the arrow was fired.
		 */
		int start_time;
		
		/**
		 * The force/speed with which this arrow was fired.
		 */
		float force;
		
                /**
                 * Angle arrow 
                 */
                float angle_arrow;
                
		/**
		 * Whether the arrow is still in the air.
		 */
                bool flying_atm;
		
		/**
		 * Targets to check for collision.
                 */
		std::vector<robinglut::target*>& targets;
		
		target* do_collision_detection(float delta_x, float delta_y);
		
	public:
		arrow(float x, float y, float z, float angle_x, float angle_y, 
		      float force, std::vector<robinglut::target*>& targets);
		
		void refresh_position();
                float get_x();
                float get_y();
                float get_z();
		void display();
                void hit();
                bool is_flying();
	};
}

#endif	/* ARROW_HPP */

