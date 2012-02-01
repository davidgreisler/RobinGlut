#include <GL/glut.h>

#include "player.hpp"
#include "obj_loader.hpp"

namespace robinglut
{
	/**
	 * Creates a new bow object with the given arrow count.
         * Vlt besser Player und nicht bow?
	 * 
         * @param arrow_count How many arrows should be in the quiver.
         */
	player::player(int arrow_count)
		: arrow_count(arrow_count), start_time(0), score(0)
	{
		obj_loader loader;
		this->arrow_model = loader.load_file("images/models/Pfeil.obj");
		this->arrow_model->scale(3);
	}
	
	/**
	 * Frees all used resources.
         */
	player::~player()
	{
		
	}
	
	/**
	 * Start drawing the bow (drawing in the sense of firing a bow, this is
	 * not a display/painting method!).
         */
	void player::start_drawing()
	{
		if (this->arrow_count)
		{
			this->start_time = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	
	/**
	 * Returns whether the bow is being drawn at the moment or not.
	 * 
	 * @return When it is drawn true, otherwise false.
         */
	bool player::is_drawing() const
	{
		return (this->start_time == 0) ? false : true;
	}
	
	/**
	 * Fires the arrow (resets timer/decreases arrow count).
         */
	void player::fire_arrow()
	{
		this->arrow_count--;
		this->start_time = 0;
	}
	
	/**
	 * Returns the current force.
	 * 
         * @return The current force, 0.0 if the bow is not being drawn, 
	 *         otherwise a value between 0.0 and 20.0.
         */
	float player::get_force() const
	{
		float force = 0.0;
		
		if (start_time > 0)
		{
			int current_time = glutGet(GLUT_ELAPSED_TIME);
			int drawing_time = current_time - this->start_time;
			force = drawing_time / 100;
			
			if (force >24.0f)
			{
				force = 24.0f;
			}
		}
		
		return force;
	}
	
	/**
	 * Sets the current level to the given one.
	 * 
         * @param level The current level.
         */
	void player::set_current_level(int level)
	{
		this->current_level = level;
	}
	
	/**
	 * Returns the current level.
         */
	int player::get_current_level() const
	{
		return this->current_level;
	}
	
	/**
	 * Returns the count of arrows in the quiver.
	 * 
         * @return How many arrows are left in the quiver.
         */
	int player::get_arrow_count() const
	{
		return this->arrow_count;
	}
	
        /**
	 * Returns the score
	 * 
         * @return Players Score
         */
        int player::get_score() const
        {
            return this->score;
            
        }
        
        /**
	 * The player has hit a target, increase the score by one.
         */
        void player::increase_score()
        {
              this->score++;
            
        }
        
	/**
	 * Adds the given amount of arrows to the quiver.
	 * 
	 * @param how_many How many arrows to add.
	 */
	void player::add_arrows(int how_many)
	{
		this->arrow_count += how_many;
	}
	
	/**
	 * Displays the bow.
         */
	void player::display()
	{
		/*glPushMatrix();
		//glLoadIdentity();
		glTranslatef(4, 9, 0);
		glRotatef(180.0f, 0, 1, 0);
		this->arrow_model->display();
		glPopMatrix();*/
	}
}
