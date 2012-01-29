#include <GL/glut.h>

#include "bow.hpp"
#include "obj_loader.hpp"

namespace robinglut
{
	/**
	 * Creates a new bow object with the given arrow count.
	 * 
         * @param arrow_count How many arrows should be in the quiver.
         */
	bow::bow(int arrow_count)
		: arrow_count(arrow_count), start_time(0)
	{
		obj_loader loader;
		this->arrow_model = loader.load_file("images/models/Pfeil.obj");
		this->arrow_model->scale(3);
	}
	
	/**
	 * Frees all used resources.
         */
	bow::~bow()
	{
		
	}
	
	/**
	 * Start drawing the bow (drawing in the sense of firing a bow, this is
	 * not a display/painting method!).
         */
	void bow::start_drawing()
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
	bool bow::is_drawing() const
	{
		return (this->start_time == 0) ? false : true;
	}
	
	/**
	 * Fires the arrow (resets timer/decreases arrow count).
         */
	void bow::fire_arrow()
	{
		this->arrow_count--;
		this->start_time = 0;
	}
	
	/**
	 * Returns the current force.
	 * 
         * @return The current force, 0.0 if the bow is not being drawn, 
	 *         otherwise a value between 0.0 and 8.0.
         */
	float bow::get_force() const
	{
		float force = 0.0;
		
		if (start_time > 0)
		{
			int current_time = glutGet(GLUT_ELAPSED_TIME);
			int drawing_time = current_time - this->start_time;
			force = drawing_time / 500;
			
			if (force > 8.0f)
			{
				force = 8.0f;
			}
		}
		
		return force;
	}
	
	/**
	 * Returns the count of arrows in the quiver.
	 * 
         * @return How many arrows are left in the quiver.
         */
	int bow::get_arrow_count() const
	{
		return this->arrow_count;
	}
	
	/**
	 * Displays the bow.
         */
	void bow::display()
	{
		/*glPushMatrix();
		//glLoadIdentity();
		glTranslatef(4, 9, 0);
		glRotatef(180.0f, 0, 1, 0);
		this->arrow_model->display();
		glPopMatrix();*/
	}
}
