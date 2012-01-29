#ifndef MODEL_HPP
#define	MODEL_HPP

#include "../lib/glm/glm.hpp"

namespace robinglut
{
	/**
	 * A 3D model, loaded by GLM, ready for display.
	 */
	class model
	{
	private:
		/**
		 * Pointer to the model.
		 */
		GLMmodel* glm_model;
		
		/**
		 * Forbid copy.
		 */
		model(const model& orig);
		
		/**
		 * Forbid assignment operator.
		 */
		model& operator=(const model& rhs);
	public:
		model(GLMmodel* glm_model);
		~model();
		
		void scale(float factor);
		
		void display();
		
	};
}

#endif	/* MODEL_HPP */

