#ifndef BOW_HPP
#define	BOW_HPP

namespace robinglut
{
	/**
	 * The bow, provides methods for drawing the bow/firing an arrow.
	 */
	class bow
	{
	private:
		/**
		 * How many arrows are left in the quiver.
		 */
		int arrow_count;
		
		/**
		 * When the drawing started.
                 */
		int start_time;
	public:
		bow(int arrow_count);
		~bow();
		
		void start_drawing();
		void fire_arrow();
		
		float get_force() const;
		int get_arrow_count() const;
		
		void display();
	};
}

#endif	/* BOW_HPP */

