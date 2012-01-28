#ifndef ARROW_HPP
#define	ARROW_HPP

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
		
	public:
		arrow(float x, float y, float z, float angle_x, float angle_y, float force);
		
		void refresh_position();

		void display();
	};
}

#endif	/* ARROW_HPP */

