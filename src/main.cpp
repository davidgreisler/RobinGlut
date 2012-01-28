#include <cstdlib>
#include <GL/glut.h>
#include <iostream>

#include "robinglut/robin_glut.hpp"

/**
 * RobinGlut - 3D first person shooter with bow and arrow.
 * 
 * @author David Greisler <kontakt@davidgreisler.de>
 * @author Daniil Tomilow <cisminor@googlemail.com>
 * @author Eric Haller
 * @param argc Argument count.
 * @param argv Command line arguments.
 */
int main(int argc, char** argv)
{
	robinglut::robin_glut main(argc, argv);
	
	return main.run();
}

