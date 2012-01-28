#ifndef RAW_LOADER_HPP
#define	RAW_LOADER_HPP

#include "GL/glut.h"

namespace robinglut
{
	/**
	 * Loads .RAW image files and returns them as GL texture.
	 * 
	 * @author David Greisler <kontakt@davidgreisler.de>
	 */
	class raw_loader
	{
	public:
		raw_loader();
		
		GLuint load_file(const char* filename, int width, int height);
		GLuint load_file(const char* filename, int width, int height, bool wrap);
	};
}

#endif	/* RAW_LOADER_HPP */

