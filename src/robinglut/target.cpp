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
	 * Creates a new target object.
	 * 
	 * @param x X position.
	 * @param y Y position.
	 * @param z Z position.
	 * @param width Targets width
	 * @param height Targets height
	 * @param texture Targets texture    
	 */
	target::target(float x, float y, float z, float width, float height, GLuint texture)
		: width(width), height(height), x(x), y(y), z(z), texture(texture), hitted(false), range(0), range_end(false)
	{
		
	}
	
	/**
	 * Copy constructor.
	 * 
         * @param orig The object to copy.
         */
	target::target(const target& orig)
		: width(orig.width), height(orig.height), x(orig.x), y(orig.y)
		, z(orig.z), texture(orig.texture)
	{
		
	}

	/**
	 * Frees all used resources.
         */
	target::~target()
	{
	}
	
	/**
	 * Returns the position of the target on the x axis.
	 * 
         * @return The position on the x axis.
         */
	float target::get_x() const
	{
		return this->x;
	}
	
	/**
	 * Returns the position of the target on the y axis.
	 * 
         * @return The position on the y axis.
         */
	float target::get_y() const
	{
		return this->y;
	}
	
	/**
	 * Returns the position of the target on the z axis.
	 * 
         * @return The position on the z axis.
         */
	float target::get_z() const
	{
		return this->z;
	}
	
	/**
	 * Returns the width of the target.
	 * 
         * @return The width of the target.
         */
	float target::get_width() const
	{
		return this->width;
	}
	
	/**
	 * Returns the height of the target.
	 * 
         * @return The height of the target.
         */
	float target::get_height() const
	{
		return this->height;
	}
	
	/**
	 * Scores the target (tells it that it was hit by an arrow).
	 * 
	 * Emits the got_scored event.
         */
	void target::score()
	{
		this->got_scored(this);
	}

         /**
	 * Set the Target as hitted
         */
        void target::set_hitted()
        {
            this->hitted = true;
        
        }
        
        /*
         * return true if the target is hitted
         */
        bool target::get_hitted()
        { 
            
            return this->hitted;
        }
        
        /*
         * set animated 
         * @param range the x range 
         * in this range the target go left and right
         */
        
        void target::set_animated(float range){
            this->range = range;
            this->range_min = this->z - range;
            this->range_max = this->z + range;
            
        }
        
	/**
	 * Displays the target.
         */
	void target::display()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		
                if(this->hitted)glColor4f(0, 0.5, 0, 0.5);
                else            glColor3f(1, 1, 1);
                
		glPushMatrix();
                
                
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(this->x, y, z);
		glTexCoord2f(0, 1);
		glVertex3f(this->x, this->y + this->height, z);
		glTexCoord2f(1, 1);
		glVertex3f(this->x, this->y + this->height, this->z + this->width);
		glTexCoord2f(1, 0);
		glVertex3f(this->x, y, this->z + this->width);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
                
                if(range && !this->hitted){
                    if(this->z < this->range_max && !range_end)
                        this->z++;
                    else if(this->z > this->range_min && range_end)
                        this->z--;
                    else range_end = range_end  ? false: true;
                        
                
                }
                
                
	}
}