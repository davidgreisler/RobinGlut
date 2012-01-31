#include <cstring>
#include <GL/glut.h>
#include <sstream>
#include <math.h>

#include "user_interface.hpp"
#include "raw_loader.hpp"
#include "arrow.hpp"

namespace robinglut
{
	/**
	 * Creates a new user interface using the given bow as data source for
	 * the remaining arrows/force display.
	 * 
         * @param bow Bow to use as data source.
         */
	user_interface::user_interface(robinglut::player& player)
		: player(player)
	{
		raw_loader loader;
		this->background_image = loader.load_file("images/top.raw", 1400, 150, false); 
	}
	
	/**
	 * Displays the user interface.
         */
	void user_interface::display()
	{
                this->draw_crosshair_force();
		this->draw_background();
		this->draw_counts();
	}
        
        /*
         * Draw the Crosshair 
         * TODO: Ist noch nicht MIttig
         */
        
        void user_interface::draw_crosshair_force(){
                float x,y;
                float radius = 0.3, radius2 = 0.5;
                
                
                glColor4f(1.0f,1.0f,1.0f, 0.5f);
                
                for(int j = 0; j < 360; j+=30)
                {       
                     glBegin(GL_QUADS);
                     if(this->player.get_force()*15 > j) // Für force = 12
                     glColor4f(1.0f,0.0f,0.0f, 0.5f);   
                     else glColor4f(1.0f,1.0f,1.0f, 0.5f);
                     
                    x = (float)radius * cos(j * M_PI/180.0f);
                    y = (float)radius * sin(j * M_PI/180.0f);
                   
                    glVertex3f(10,y+10,x);
                    
                    x = (float)radius2 * cos(j * M_PI/180.0f); 
                    y = (float)radius2 * sin(j * M_PI/180.0f);
                    
                    glVertex3f(10,y+10,x);
                    
                    x = (float)radius2 * cos((j+15) * M_PI/180.0f);
                    y = (float)radius2 * sin((j+15) * M_PI/180.0f);
                    
                    glVertex3f(10,y+10,x);
                    
                    x = (float)radius * cos((j+15) * M_PI/180.0f);
                    y = (float)radius * sin((j+15) * M_PI/180.0f);
                    
                    glVertex3f(10,y+10,x);

                    glEnd();
                }
                
                glPopMatrix();

        }
        
        
        
        
        
	/**
	 * Draws the bow force, respectively how strong the bow is drawn.
         
	void user_interface::draw_force()
	{       
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, this->force_image);
            glColor3f(1, 1, 1);
		glPushMatrix();
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(2, 10, 0.1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(2, 10.1, 0.1);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(2, 10.1, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(2, 10, 0.01);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
	}
        */
        
	/**
	 * Draws the background image.
         */
	void user_interface::draw_background()
	{
           //     glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, this->background_image);
		
		glColor3f(1, 1, 1);
		glPushMatrix();
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(2, 11.10, -1.35);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(2, 11.35, -1.35);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(2, 11.35, 1.35);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(2, 11.10, 1.35);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
                //glEnable(GL_LIGHTING);
	}

	/**
	 * Draws the level/points/arrows left numbers.
         */
	void user_interface::draw_counts()
	{
		std::stringstream ss;
		
		// Level
		
		ss <<this->player.get_current_level();
		this->print_text(1.5, 10.91, -0.65, ss.str().c_str(), 0, 0, 0, 0.8);
		ss.str("");
		
		// Points
		
		ss << this->player.get_score();
		this->print_text(1.5, 10.91, -0.14, ss.str().c_str(), 0, 0, 0, 0.8);
		ss.str("");

		// Arrows left.
		
		ss << this->player.get_arrow_count();
		this->print_text(1.5, 10.91, 0.38, ss.str().c_str(), 0, 0, 0, 0.8);
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
