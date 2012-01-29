/* 
 * File:   target.hpp
 * Author: daniil
 *
 * Created on 29. Januar 2012, 13:31
 */
#include <GL/gl.h>
namespace robinglut
{
	
#ifndef TARGET_HPP
#define	TARGET_HPP

class target {
public:
    target(float x, float y,float z, int width, int height,  GLuint texture);
    target(const target& orig);
    virtual ~target();
    void display();
private:
    int width,height;
    float x,y,z;
    GLuint texture;

};

#endif	/* TARGET_HPP */

}