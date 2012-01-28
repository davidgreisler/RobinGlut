#include <GL/gl.h>
#include <cmath>

#include "arrow.hpp"
#include "../../pfeil.hpp"

#define PI 3.14159265358979323846 

namespace robinglut
{

	arrow::arrow(float x, float y, float z) :
	x(x), y(y), z(z), speed(0), start(false), start_spannen(false), start_time(0), AnzahlPfeile(4)
	{

	}

	void arrow::display()
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);
		glTranslatef(this->x, this->y, this->z);
		glRotatef(270, 0, 0, 1);
		glScalef(1, 5, 1);
		drawpfeil();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	void arrow::Animate(int time, float anglex)
	{
		if (!this->start) return;
		if (y < 0)
		{
			this->stopAnimate();
		}
		this->start_time = start_time = (this->start_time != 0) ? this->start_time : time;

		float t = (float) (time - start_time) / 1000;
		float x = (this->speed * t) * std::cos(anglex * PI / 180 * -1);

		this->x += x;
		this->y += -9.81 / 2 * t * t + this->speed * t * std::sin(anglex * PI / 180 * -1);

	}

	void arrow::startAnimate()
	{
		if (this->AnzahlPfeile < 1) return;
		this->start = true;
	}

	bool arrow::stopAnimate()
	{
		this->start = false;
		this->x = 2.0;
		this->y = 9;
		this->z = 0;
		this->speed = 0;
		this->start_time = 0;
		this->AnzahlPfeile--;
		return true;
	}

	void arrow::spannen(int time)
	{
		if (!this->start_spannen) return;
		if (this->AnzahlPfeile < 1) return;
		this->start_time = start_time = (this->start_time != 0) ? this->start_time : time;

		if (this->speed > 8)
		{
			this->stopSpannen();
			this->startAnimate();
			return;
		}

		if (time - start_time > 500)
		{
			this->speed += 2.0f;
			this->start_time = 0;
		}
	}

	void arrow::activeSpannen()
	{

		this->start_spannen = true;
	}

	void arrow::stopSpannen()
	{
		if (this->AnzahlPfeile < 1) return;
		this->start_spannen = false;
		this->start_time = 0;
		this->start = true;
	}

	float arrow::getSpeed()
	{
		return this->speed;
	}

	/**
	 * Returns the amount of arrows left.
	 * 
         * @return The amount of arrows. 
         */
	int arrow::get_arrow_count()
	{
		return this->AnzahlPfeile;
	}

}
