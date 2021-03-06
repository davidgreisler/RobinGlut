#include <GL/gl.h>
#include <iostream>

#include "level.hpp"
#include "raw_loader.hpp"
#include "robin_glut.hpp"


namespace robinglut
{

	/**
	 * Creates a new level object.
	 * 
	 * @param game_player The player.
         */
	level::level(robinglut::player* game_player)
		: last_fired_arrow(0), anglex(0.0f), angley(0.0f), anglez(0.0f), lastx(0), lasty(0), player(game_player)
	{
		this->ui = new user_interface(*(this->player));

                //this->map = new robinglut::heightmap("images/tesseract.raw", 120, 120);
                
		raw_loader loader;
		this->butt_texture = loader.load_file("images/scheibe1.raw", 203, 208, false);
		this->ground_texture = loader.load_file("images/boden.raw", 410, 410, false);
		this->area_left_texture = loader.load_file("images/left_scope.raw", 1280, 698, false);
		this->area_center_texture = loader.load_file("images/center_scope.raw", 1280, 698, false);
		this->area_right_texture = loader.load_file("images/right_scope.raw", 1280, 698, false);
		
		this->button_pressed[0] = false;
		this->button_pressed[1] = false;
		this->button_pressed[2] = false;
	}
	
	/**
	 * Initializes the level. Do not forget to call this. Call this 
	 * immediately after constructing the level (adding targets, etc.).
         */
	void level::initialize()
	{
		std::vector<target*>::const_iterator it;
		for (it = this->targets.begin(); it != this->targets.end(); it++)
		{
			(*it)->got_scored += event::event_listener(this, &level::increase_score);
		}
	}
	
	/**
	 * Increases the score by one and removes the target that got hit.
	 * 
         * @param hit_target The target that got hit.
         */
	void level::increase_score(target* hit_target)
	{
                if(hit_target->get_hitted()) return;
            
		this->player->increase_score();
                hit_target->set_hitted();
                
                // Könnte man bestimmt besser machen?^^
                int i = 0;
		std::vector<target*>::const_iterator it;
		for (it = this->targets.begin(); it != this->targets.end(); it++)
		{
                    if((*it)->get_hitted()) i++;
			
		}
                
                if (i == this->targets.size()) this->finished_event(123);
     
	}
	
	/**
	 * Displays the current view.
         */
	void level::display()
	{
		this->ui->display();
		
		glRotatef(this->anglex, 0, 0, 1);
		glRotatef(this->angley, 0, 1, 0);
		
                // Mit pfeil mitfliegen
                if(this->last_fired_arrow && this->last_fired_arrow->is_flying())
                glTranslatef(-this->last_fired_arrow->get_x()+15,
                             -this->last_fired_arrow->get_y(),
                             -this->last_fired_arrow->get_z());
                else if(this->last_fired_arrow && !this->last_fired_arrow->is_flying())
                glTranslatef(0,0,0);
                 
                
		this->player->display();

                this->draw_targets();
		this->draw_ground();
		//this->draw_sky();
		this->draw_surrounding_area();
		this->draw_arrows();
	}
	
	/**
	 * Draws the targets
	 */
	void level::draw_targets()
	{
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
		int button_idx;
		lastx = x;
		lasty = y;
		
		if (GLUT_LEFT_BUTTON == button)
		{
			button_idx = 0;
                        //Menu clicked
                        if(x > 860 && x <1010 && y > 15 && y < 60)
                            this->finished_event(123);
                        
		}
		else if (GLUT_MIDDLE_BUTTON == button)
		{
			button_idx = 1;
		}
		else if (GLUT_RIGHT_BUTTON == button)
		{
			button_idx = 2;
			
			if (GLUT_DOWN == state)
			{
				this->start_drawing();
			}
			else
			{
				this->fire_arrow();
			}
		}
		
		this->button_pressed[button_idx] = ((GLUT_DOWN == state) ? true : false);
                
                
           
	}
	
	/**
	 * Starts drawing the bow (if possible, e.g. enough arrows are in the 
	 * quiver).
         */
	void level::start_drawing()
	{
		if (this->player->get_arrow_count() > 0)
		{
			this->player->start_drawing();
		}
	}

	/**
	 * Ends drawing and fires the arrow (if applicable).
         */
	void level::fire_arrow()
	{
		if (this->player->is_drawing())
		{
			last_fired_arrow = new arrow(2, 9, 0,
						this->anglex, this->angley,
						this->player->get_force(),
						this->targets);
			this->arrows.push_back(last_fired_arrow);
			this->player->fire_arrow();
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

		// Uncomment this if you don't want it to be possible to move
		// the camera when drawing the bow.
		
		//if (!this->bow->is_drawing())
		//{
			anglex += (float) 0.5f * diffy;
			angley += (float) 0.5f * diffx;
		//}
		
		//zoom -= (float) 0.05f * diffx;

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
		glTexCoord2f(0, 0); glVertex3f(500, 0, 500);
		glTexCoord2f(0, 30); glVertex3f(-500, 0, 500);
		glTexCoord2f(30, 30); glVertex3f(-500, 0, -500);
		glTexCoord2f(30, 0); glVertex3f(500, 0, -500);
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
		glColor3f(0.329, 0.501, 0.639);
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(200, 100, 200);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-200, 100, 200);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-200, 100, -200);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(200, 100, -200);
		glEnd();
		glPopMatrix();
	}

	/**
	 * Draws the surrounding area.
         */
	void level::draw_surrounding_area()
	{
                int height = 250;
                int width = 500;
                int distance = 500;
            
		glEnable(GL_TEXTURE_2D);
		glColor3f(1, 1, 1);
		glBindTexture(GL_TEXTURE_2D, this->area_center_texture);

		glPushMatrix();
		glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f);  glVertex3f(distance, 0,     width);
                    glTexCoord2f(0.0f, 1.0f);  glVertex3f(distance, height, width);
                    glTexCoord2f(1.0f, 1.0f);  glVertex3f(distance, height, -width);
                    glTexCoord2f(1.0f, 0.0f);  glVertex3f(distance, 0,     -width);
		glEnd();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, this->area_left_texture);
		glPushMatrix();
             
		glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0,        -distance);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(width,  height,      -distance);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, height,     -distance);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, 0,       -distance);
		glEnd();
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, this->area_right_texture);
		glPushMatrix();
          
		glBegin(GL_QUADS);
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(width, 0, distance);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(width, height, distance);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-width,height, distance);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, 0, distance);
		glEnd();
		glPopMatrix();
		
		glDisable(GL_TEXTURE_2D);
	}
}
