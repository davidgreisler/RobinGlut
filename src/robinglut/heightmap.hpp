/* 
 * File:   heightmap.hpp
 * Author: daniil
 *
 * Created on 29. Januar 2012, 01:01
 */

#ifndef HEIGHTMAP_HPP
#define	HEIGHTMAP_HPP

namespace robinglut
{
    class heightmap {
    public:
        heightmap(const char* filename,int width, int height);
        heightmap(const heightmap& orig);
        virtual ~heightmap();
    
   void RenderHeightMap();
    private:
    int getHeight(int X, int Y);
    void SetVertexColor(int x, int y);
    
    char* map;
    };
}
#endif	/* HEIGHTMAP_HPP */

