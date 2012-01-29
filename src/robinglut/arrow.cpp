#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "arrow.hpp"
#include "../../pfeil.hpp"
#include "target.hpp"


namespace robinglut
{
	/**
	 * Creates a new arrow object using the given parameters.
	 * 
         * @param x X position where the arrow was fired.
         * @param y Y position where the arrow was fired.
         * @param z Z position where the arrow was fired.
         * @param angle_x X angle in which the arrow was fired.
         * @param angle_y Y angle in which the arrow was fired.
         * @param force The force.
         */
	arrow::arrow(float x, float y, float z, float angle_x, float angle_y, float force, std::vector<robinglut::target*>& targets)
		: x(x), y(y), z(z), angle_x(angle_x), angle_y(angle_y), force(force), angle_arrow(0), flying_atm(true), targets(targets)
	{
		this->start_time = glutGet(GLUT_ELAPSED_TIME);
	}

	/**
	 * Displays the arrow at it's current position.
         */
	void arrow::display()
	{
		this->refresh_position();
		
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);
              
                
		glTranslatef(this->x, this->y, this->z );
		glRotatef(-this->angle_y, 0, 1, 0);
                glRotatef(270, 0, 0, 1);
          
		glScalef(1, 5, 1);
		drawpfeil();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
        /*
         * Getter for x,y,z
         */
        float  arrow::get_x(){return this->x;}
        float  arrow::get_y(){return this->y;}
        float  arrow::get_z(){return this->z;}
        
        /**
         * Set Arrow that it hit the target
         */
        void arrow::hit(){this->flying_atm = true;}
        
        
        /* Is this Arrow hit a Target?*/
        bool arrow::is_flying(){return this->flying_atm;}
        
        
	/**
	 * Refreshs the current position of the arrow.
         */
	void arrow::refresh_position()
	{
		if (this->flying_atm)
		{
			int time = glutGet(GLUT_ELAPSED_TIME);

			float t = (float) (time - this->start_time) / 1000;

			float delta_x = (this->force * t) * std::cos(this->angle_x * M_PI / 180 * -1);
			float delta_y = -9.81 / 2 * t * t + this->force * t * std::sin(this->angle_x * M_PI / 180 * -1);
			
			target* hit = this->do_collision_detection(delta_x, delta_y);
			
			if (0 != hit)
			{
				this->x = hit->get_x() - 3;
				hit->score();
				this->flying_atm = false;
			}
			else
			{
				this->x += delta_x;
			}
			
			this->y += delta_y;
                        this->z = this->x * std::tan(this->angle_y*M_PI/180);
                        this->angle_arrow = std::atan((9 - this->x)*M_PI / 180);

			if (this->y < 0)
			{
				this->y = 0;
				this->flying_atm = false;
			}
		}
	}
	
	/**
	 * Does collision detection for all known targets and returns the target
	 * that got hit (or 0 if no target was hit).
	 * 
         * @param delta_x How the x position of the arrow will change after
	 *        position refresh.
         * @param delta_y Same for the y position.
         * @return When a target was hit, this returns the target that was hit,
	 *         otherwise 0.
         */
	target* arrow::do_collision_detection(float delta_x, float delta_y)
	{
		std::vector<target*>::const_iterator it;
		for (it = this->targets.begin(); it != this->targets.end(); it++)
		{
			target* current_target = *it;
			
			if (this->get_x() >= current_target->get_x())
			{
				// Arrow is behind the target, won't hit anymore.
				
				continue;
			}
			
			if ((this->get_x() + delta_x) <= current_target->get_x())
			{
				// Arrow is before the target, no hit yet.
				
				continue;
			}
			
			// Arrow hits the target on the X axis.
			
			if (this->get_y() < current_target->get_y())
			{
				// Too low, arrow is flying under the target.
				
				continue;
			}
			
			float temp = current_target->get_y() + current_target->get_height();
			if (this->get_y() > temp)
			{
				// Too high, arrow is flying over target.
				
				continue;
			}
			
			// Arrow hits on the Y axis.
			
			if (this->get_z() <= current_target->get_z())
			{
				// Arrow flies past on the left side.
				
				continue;
			}
			
			temp = current_target->get_z() + current_target->get_width();
			if (this->get_z() >= temp)
			{
				// Arrow flies past on the right side.
				
				continue;
			}
			
			// Hit!
			
			return current_target;
		}
		
		return 0;
	}
}
