#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "arrow.hpp"
#include "../../pfeil.hpp"

#define PI 3.14159265358979323846 

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
	arrow::arrow(float x, float y, float z, float angle_x, float angle_y, float force)
		: x(x), y(y), z(z), angle_x(angle_x), angle_y(angle_y), force(force)
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
		glRotatef(-this->angle_y, 0, 1, 0);
		glTranslatef(this->x, this->y, this->z);
		glRotatef(270, 0, 0, 1);
		glScalef(1, 5, 1);
		drawpfeil();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	/**
	 * Refreshs the current position of the arrow.
         */
	void arrow::refresh_position()
	{
		if (this->y > 0)
		{
			int time = glutGet(GLUT_ELAPSED_TIME);

			float t = (float) (time - this->start_time) / 1000;
			float x = (this->force * t) * std::cos(this->angle_x * PI / 180 * -1);

			this->x += x;
			this->y += -9.81 / 2 * t * t + this->force * t * std::sin(this->angle_x * PI / 180 * -1);
			
			if (this->y < 0)
			{
				this->y = 0;
			}
		}
	}
}
