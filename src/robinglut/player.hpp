#ifndef BOW_HPP
#define	BOW_HPP

#include "model.hpp"
#include "game.hpp"

namespace robinglut
{
	/**
	 * The bow, provides methods for drawing the bow/firing an arrow.
	 */
	class player
	{
		/**
		 * For changing the level counter.
		 */
		friend class game;
	private:
		/**
		 * How many arrows are left in the quiver.
		 */
		int arrow_count;
		
		/**
		 * When the drawing of the bow started.
                 */
		int start_time;
		
		/**
		 * Arrow model.
		 */
		model* arrow_model;
		
		/**
		 * The current score.
		 */
		int score;
		
		/**
		 * The current level.
                 */
		int current_level;
		
	protected:
		void set_current_level(int level);
		
	public:
		player(int arrow_count);
		~player();
		
		void start_drawing();
		bool is_drawing() const;
		void fire_arrow();
		
		float get_force() const;
		int get_arrow_count() const;
                int get_score() const;
		void add_arrows(int how_many);
                void increase_score();
		int get_current_level() const;
		
		void display();
	};
}

#endif	/* BOW_HPP */

