#include <cstring>
#include <GL/glut.h>
#include <sstream>

#include "user_interface.hpp"
#include "raw_loader.hpp"
#include "arrow.hpp"

namespace robinglut
{

	user_interface::user_interface(arrow* p) : p(p)
	{
		raw_loader loader;
		this->background_image = loader.load_file("images/top.raw", 1080, 85, false);
	}
	
	/**
	 * Displays the user interface.
         */
	void user_interface::display()
	{
		this->draw_speed();
		this->draw_background();
		this->draw_counts();
	}
	
	void user_interface::draw_speed()
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);

		glBegin(GL_QUADS);
		glColor3f(1, 0, 0);

		glVertex3f(2, 10, -1.3);
		glVertex3f(2, 10.1 + this->p->getSpeed() / 15, -1.3);
		glVertex3f(2, 10.1 + this->p->getSpeed() / 15, -1.2);
		glVertex3f(2, 10, -1.2);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}

	/**
	 * Draws the background image.
         */
	void user_interface::draw_background()
	{
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, this->background_image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glColor3f(1, 1, 1);
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2, 11.15, -1.35);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(2, 11.35, -1.35);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(2, 11.35, 1.35);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(2, 11.15, 1.35);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	/**
	 * Draws the level/points/arrows left numbers.
         */
	void user_interface::draw_counts()
	{
		std::stringstream ss;
		
		// Level
		
		ss << "1";
		this->print_text(1.5, 10.92, -0.65, ss.str().c_str(), 0, 0, 0, 0.8);
		ss.str("");
		
		// Points
		
		ss << "0";
		this->print_text(1.5, 10.92, -0.14, ss.str().c_str(), 0, 0, 0, 0.8);
		ss.str("");

		// Arrows left.
		
		ss << this->p->get_arrow_count();
		this->print_text(1.5, 10.92, 0.345, ss.str().c_str(), 0, 0, 0, 0.8);
		ss.str("");
	}

	/**
	 * Prints the given text on the screen at the given position using the
	 * given colors.
	 * 
	 * @param x The X position.
         * @param y The Y position.
         * @param z The Z position.
         * @param text The text to display.
         * @param r Red.
         * @param g Green.
         * @param b Blue.
         * @param a Alpha.
         */
	void user_interface::print_text(float x, float y, float z, 
	                                const char* text, float r, 
	                                float g, float b, float a)
	{
		if (std::strlen(text) > 0)
		{
			bool blending = glIsEnabled(GL_BLEND) ? true : false;

			glPushMatrix();
			glEnable(GL_BLEND);

			glEnable(GL_LINE_SMOOTH);
			glLineWidth(2.0);
			glColor4f(r, g, b, a);
			glRasterPos3f(x, y, z);

			while (*text)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
				text++;
			}

			if (!blending)
			{
				glDisable(GL_BLEND);
			}
			
			glPopMatrix();
		}
	}

}
