#ifndef MODEL_HPP
#define	MODEL_HPP

#include "../lib/glm/glm.hpp"

namespace robinglut
{
	
	
	class model
	{
	private:
		GLMmodel* glm_model;
		
		model(const model& orig);
		model& operator=(const model& rhs);
	public:
		model(GLMmodel* glm_model);
		~model();
		
		void scale(float factor);
		
		void display();
		
	};
}

#endif	/* MODEL_HPP */

