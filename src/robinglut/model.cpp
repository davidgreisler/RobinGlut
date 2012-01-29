#include "model.hpp"
#include "../lib/glm/glm.hpp"

namespace robinglut
{
	/**
	 * Creates a new model object for the given GLM model.
	 */
	model::model(GLMmodel* glm_model)
		: glm_model(glm_model)
	{

	}

	/**
	 * Frees all used resources (the GLM model).
	 */
	model::~model()
	{
		glmDelete(this->glm_model);
	}

	/**
	 * Scales the model by the given factor.
	 * 
	 * @param factor The scale factor.
	 */
	void model::scale(float factor)
	{
		glmScale(this->glm_model, (GLfloat)factor);
	}
	
	/**
	 * Displays the model.
	 */
	void model::display()
	{
		glmDraw(this->glm_model, GLM_SMOOTH);
	}

}