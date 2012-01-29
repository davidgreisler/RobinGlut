/* 
 * File:   heightmap.cpp
 * Author: daniil
 * NOT USED NOW
 * Created on 29. Januar 2012, 01:01
 */

#include "heightmap.hpp"
#include <fstream>
#include <GL/gl.h>
#define MAP_SIZE 120
#define STEP_SIZE 10
namespace robinglut
{

heightmap::heightmap(const char* filename,int width, int height) {

		std::ifstream file;
		file.open(filename);
		
		if (!file.is_open())
		{return;}
		
		this->map = new char[width * height * 3];

		for (int i = height - 1; i >= 0; --i)
		{
			char* pos = this->map + (width * 3) * i;
			file.read(pos, width * 3);
		}
		
		file.close();
    
}

heightmap::heightmap(const heightmap& orig) {
}

heightmap::~heightmap() {
}

int heightmap::getHeight(int X, int Y)          // This Returns The Height From A Height Map Index
{
    int x = X % MAP_SIZE;                   // Error Check Our x Value
    int y = Y % MAP_SIZE;                   // Error Check Our y Value
 
    if(!this->map) return 0;  
    return this->map[x + (y * MAP_SIZE)];          // Index Into Our Height Array And Return The Height
}

void heightmap::SetVertexColor(int x, int y)     // This Sets The Color Value For A Particular Index
{                               // Depending On The Height Index
    if(!this->map) return;                 // Make Sure Our Height Data Is Valid
 
    float fColor = -0.15f + (this->getHeight( x, y ) / 256.0f);
 
    // Assign This Blue Shade To The Current Vertex
    glColor3f(0.0f, 1.0f, fColor );
}

void heightmap::RenderHeightMap()             // This Renders The Height Map As Quads
{
    int X = 0, Y = 0;                   // Create Some Variables To Walk The Array With.
    int x, y, z;                        // Create Some Variables For Readability
 
    if(!this->map) return;   
    // Make Sure Our Height Data Is Valid
    glPushMatrix();
   
       // What We Want To Render
   
     glBegin( GL_QUADS );   
      glTranslatef(-5,0,-5);
                     // Render Lines Instead
    for ( X = 0; X < (MAP_SIZE-STEP_SIZE); X += STEP_SIZE )
    for ( Y = 0; Y < (MAP_SIZE-STEP_SIZE); Y += STEP_SIZE )
    {
        // Get The (X, Y, Z) Value For The Bottom Left Vertex
        x = X;                         
        y = this->getHeight( X, Y ); 
        z = Y;                         
 
        // Set The Color Value Of The Current Vertex
        SetVertexColor( x, z);
 
        glVertex3i(x, y-100, z);            // Send This Vertex To OpenGL To Be Rendered
 
        // Get The (X, Y, Z) Value For The Top Left Vertex
        x = X;                                     
        y = this->getHeight( X, Y + STEP_SIZE ); 
        z = Y + STEP_SIZE ;                        
         
        // Set The Color Value Of The Current Vertex
        SetVertexColor( x, z);
 
        glVertex3i(x, y-100, z);            // Send This Vertex To OpenGL To Be Rendered
 
        // Get The (X, Y, Z) Value For The Top Right Vertex
        x = X + STEP_SIZE;
        y = this->getHeight( X + STEP_SIZE, Y + STEP_SIZE );
        z = Y + STEP_SIZE ;
 
        // Set The Color Value Of The Current Vertex
        SetVertexColor( x, z);
         
        glVertex3i(x, y-100, z);            // Send This Vertex To OpenGL To Be Rendered
 
        // Get The (X, Y, Z) Value For The Bottom Right Vertex
        x = X + STEP_SIZE;
        y = this->getHeight( X + STEP_SIZE, Y );
        z = Y;
 
        // Set The Color Value Of The Current Vertex
        SetVertexColor( x, z);
 
        glVertex3i(x, y-100, z);            // Send This Vertex To OpenGL To Be Rendered
    }
glEnd();
glPopMatrix();
}

}