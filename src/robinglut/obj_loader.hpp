#ifndef OBJ_LOADER_HPP
#define	OBJ_LOADER_HPP

#include "model.hpp"

namespace robinglut
{
	class obj_loader
	{
	private:
		
	public:
		model* load_file(const char* filename) const;
	};
}

#endif	/* OBJ_LOADER_HPP */

