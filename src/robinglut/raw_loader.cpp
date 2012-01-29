#include "raw_loader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

namespace robinglut
{
	/**
	 * Creates a new .RAW loader object.
         */
	raw_loader::raw_loader()
	{
		
	}
	
	/**
	 * Loads the .RAW file under the given filename into memory and returns
	 * the opengl texture identifier.
	 * 
         * @param filename The filename.
         * @param width Width of the texture.
         * @param height Height of the texture.
         * @return The identifier.
         */
	GLuint raw_loader::load_file(const char* filename, int width, int height)
	{
		return raw_loader::load_file(filename, width, height, true);
	}
	
	GLuint raw_loader::load_file(const char* filename, int width, int height, bool wrap)
	{
		GLuint result;
		char* data;
		
		std::ifstream file;
		file.open(filename);
		
		if (!file.is_open())
		{
			std::stringstream ss;
			ss << "Failed to open file '" << filename << "'.";
			throw std::runtime_error(ss.str().c_str());
		}
		
		data = new char[width * height * 3];
		
		// .RAW files are stored upside-down.
		
		for (int i = height - 1; i >= 0; --i)
		{
			char* pos = data + (width * 3) * i;
			file.read(pos, width * 3);
		}
		
		file.close();
		
		// Allocate texture name.
		
		glGenTextures(1, &result);
		
		// Select texture.
		
		glBindTexture(GL_TEXTURE_2D, result);
		
		// ?
		
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		// Set some texture filtering properties.
	
		if (wrap)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		}
			
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		
		delete[] data;
		
		return result;
	}
}
