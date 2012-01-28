#include <GL/glut.h>

#include "bow.hpp"

namespace robinglut
{
	bow::bow(int arrow_count)
		: arrow_count(arrow_count), start_time(0)
	{
		
	}
	
	bow::~bow()
	{
		
	}
		
	void bow::start_drawing()
	{
		if (this->arrow_count)
		{
			this->start_time = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	
	void bow::fire_arrow()
	{
		this->arrow_count--;
		this->start_time = 0;
	}
		
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
	
	int bow::get_arrow_count() const
	{
		return this->arrow_count;
	}
		
	void bow::display()
	{
		
	}
}
