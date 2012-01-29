#include <GL/gl.h>
#include <iostream>

#include "level.hpp"
#include "raw_loader.hpp"
#include "robin_glut.hpp"


namespace robinglut
{

	/**
	 * Creates a new level object.
         */
	level::level()
		: anglex(0.0f), angley(0.0f), anglez(0.0f), lastx(0), lasty(0)
	{
                
		this->bow = new robinglut::bow(10);
		this->ui = new user_interface(*(this->bow));

                //this->map = new robinglut::heightmap("images/tesseract.raw", 120, 120);
                
		raw_loader loader;
		this->butt_texture = loader.load_file("images/scheibe1.raw", 203, 208, false);
		this->ground_texture = loader.load_file("images/boden.raw", 410, 410, false);
		this->area_left_texture = loader.load_file("images/left_scope.raw", 1280, 698, false);
		this->area_center_texture = loader.load_file("images/center_scope.raw", 1280, 698, false);
		this->area_right_texture = loader.load_file("images/right_scope.raw", 1280, 698, false);
		
                this->targets.push_back(new robinglut::target(50,10,0,5.0,5.0, this->butt_texture));
                this->targets.push_back(new robinglut::target(50,10,10,5.0,5.0, this->butt_texture));
                this->targets.push_back(new robinglut::target(50,10,-10,5.0,5.0, this->butt_texture));
                
		this->Buttons[0] = 0;
		this->Buttons[1] = 0;
		this->Buttons[2] = 0;
	}
	
	/**
	 * Displays the current view.
         */
	void level::display()
	{
		this->ui->display();
		
		glRotatef(this->anglex, 0, 0, 1); // Blickwinkel Rotieren
		glRotatef(this->angley, 0, 1, 0);
                
               
		
                this->draw_targets();
                
		this->draw_ground();
      
		this->draw_sky();
		this->draw_surrounding_area();
		 this->draw_arrows();

	}
	/* 
         *      Draw the targets
         */
        
        void level::draw_targets(){
                std::vector<target*>::const_iterator it;
		for (it = this->targets.begin(); it != this->targets.end(); it++)
		{
			(*it)->display();
		}
        
        }
        
        
	/**
	 * Draws all arrows that have already been fired.
         */
	void level::draw_arrows()
	{
		std::vector<arrow*>::const_iterator it;
		for (it = this->arrows.begin(); it != this->arrows.end(); it++)
		{
			(*it)->display();
		}
	}
	
	/**
	 * Mouse button handler. Fires arrows on right click.
	 * 
         * @param button Which button was pressed/released.
         * @param state Whether it was pressed or released.
         * @param x X position.
         * @param y Y position.
         */
	void level::on_mouse(int button, int state, int x, int y)
	{
		//if (!mouse_listen) return;
		lastx = x;
		lasty = y;
		switch (button)
		{
			case GLUT_LEFT_BUTTON:
				Buttons[0] = ((GLUT_DOWN == state) ? 1 : 0);
				break;
			case GLUT_MIDDLE_BUTTON:
				Buttons[1] = ((GLUT_DOWN == state) ? 1 : 0);
				break;
			case GLUT_RIGHT_BUTTON:
				if (state == 0)
				{
					this->bow->start_drawing();
				}
				else
				{
					this->arrows.push_back(new robinglut::arrow(2,9,0, this->anglex, this->angley, this->bow->get_force()));
					this->bow->fire_arrow();
				}
				break;
			default:
				break;
		}
	}

	/**
	 * Refreshes the x/y angle on mouse motion.
	 * 
         * @param x New X position.
         * @param y New Y position.
         */
	void level::on_active_motion(int x, int y)
	{
		int diffx = x - lastx;
		int diffy = y - lasty;
		lastx = x;
		lasty = y;

		if (Buttons[0] && Buttons[1])
		{
			//zoom -= (float) 0.05f * diffx;
		}
		else if (Buttons[0])
		{
			anglex += (float) 0.5f * diffy;
			angley += (float) 0.5f * diffx;
			//printf("%f %f\n", anglex, angley);
		}

		glutPostRedisplay();
	}



	/**
	 * Draws the ground.
         */
	void level::draw_ground()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->ground_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glTexCoord2f(0, 0);
		glVertex3f(100, 0, 100);
		glTexCoord2f(0, 2);
		glVertex3f(-100, 0, 100);
		glTexCoord2f(2, 2);
		glVertex3f(-100, 0, -100);
		glTexCoord2f(2, 0);
		glVertex3f(100, 0, -100);
		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}

	/**
	 * Draws the sky.
         */
	void level::draw_sky()
	{
		glPushMatrix();
		glBegin(GL_QUADS);
		glColor3f(0.6, 0.6, 0.9);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(100, 100, 100);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-100, 100, 100);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-100, 100, -100);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(100, 100, -100);
		glEnd();
		glPopMatrix();
	}

	/**
	 * Draws the surrounding area.
         */
	void level::draw_surrounding_area()
	{
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, this->area_center_texture);

		glPushMatrix();
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(100, 0, 100);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(100, 100, 100);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(100, 100, -100);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(100, 0, -100);
		glEnd();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, this->area_left_texture);
		glPushMatrix();
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(100, 0, -100);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(100, 100, -100);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-100, 100, -100);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-100, 0, -100);
		glEnd();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, this->area_right_texture);
		glPushMatrix();
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(100, 0, 100);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(100, 100, 100);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-100, 100, 100);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-100, 0, 100);
		glEnd();
		glPopMatrix();
		
		glDisable(GL_TEXTURE_2D);
	}
}
