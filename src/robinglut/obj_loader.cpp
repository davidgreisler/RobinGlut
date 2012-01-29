#include "obj_loader.hpp"
#include "../lib/glm/glm.hpp"

namespace robinglut
{
	/**
	 * Loads a model from a .obj file and returns the model object.
	 * 
         * @param filename Filename of the model.
         * @return 
         */
	model* obj_loader::load_file(const char* filename) const
	{
		char* fptr = (char*)filename;
		GLMmodel* glm_model = glmReadOBJ(fptr);
	
		glmUnitize(glm_model);
		glmFacetNormals(glm_model);
		glmVertexNormals(glm_model, 90.0);
		
		model* result = new model(glm_model);
		
		return result;
	}
}
