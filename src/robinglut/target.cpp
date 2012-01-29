/* 
 * File:   target.cpp
 * Author: daniil
 * 
 * Created on 29. Januar 2012, 13:31
 */

#include "target.hpp"
#include <iostream>
#include <GL/gl.h>
namespace robinglut
{
    /**
	 * Draws a butt at the given position.
	 * 
         * @param x X position.
         * @param y Y position.
         * @param z Z position.
         * @param width Targets width
         * @param height Targets height
         * @param texture Targets texture    
         */
    target::target(float x, float y,float z, int width, int height,  GLuint texture) : 
    width(width), height(height), x(x),y(y), z(z), texture(texture) {
    }


    void target::display(){
            glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, this->texture);
                    glColor3f(1, 1, 1);
                    glPushMatrix();

                    glBegin(GL_QUADS);
                    glTexCoord2f(0, 0); glVertex3f(this->x, y, z);
                    glTexCoord2f(0, 1); glVertex3f(this->x, this->y + this->height, z);
                    glTexCoord2f(1, 1); glVertex3f(this->x, this->y + this->height, this->z + this->width);
                    glTexCoord2f(1, 0); glVertex3f(this->x, y, this->z + this->width);
                    glEnd();

                    glPopMatrix();
                    glDisable(GL_TEXTURE_2D);

    }
     
        /*
         * Check the collision between target and arrow
         */
        
        bool target::check_collision(float arrow_x, float arrow_y, float arrow_z){
            if(arrow_x >= this->x
               && arrow_y >= this->y
               && arrow_y <= this->y + this->height
               && arrow_z >= this->z
               && arrow_z <= this->z + this->width)
            return true;
            return false;
       
  
        }
    target::target(const target& orig) {
    }

    target::~target() {
    }

}