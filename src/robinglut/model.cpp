#include "model.hpp"
#include "../lib/glm/glm.hpp"

namespace robinglut
{

	model::model(GLMmodel* glm_model)
		: glm_model(glm_model)
	{

	}

	model::~model()
	{
		glmDelete(this->glm_model);
	}

	void model::scale(float factor)
	{
		glmScale(this->glm_model, (GLfloat)factor);
	}
	
	void model::display()
	{
		glmDraw(this->glm_model, GLM_SMOOTH);
	}

}