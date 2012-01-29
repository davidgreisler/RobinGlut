#ifndef BOW_HPP
#define	BOW_HPP

#include "model.hpp"

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
                int score;
		
		/**
		 * When the drawing started.
                 */
		int start_time;
		
		/**
		 * Arrow model.
		 */
		model* arrow_model;
	public:
		bow(int arrow_count);
		~bow();
		
		void start_drawing();
		bool is_drawing() const;
		void fire_arrow();
		
		float get_force() const;
		int get_arrow_count() const;
                int get_score() const;
                void hit_one();
		
		void display();
	};
}

#endif	/* BOW_HPP */

