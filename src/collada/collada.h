#ifndef __COLLADA_H__
#define __COLLADA_H__

#include "meshes/models/dynamic_mesh.h"
#include <string>

class domCOLLADA;

namespace collada
{
	bool load_mesh(meshes::dynamic_mesh& msh, domCOLLADA* dom, std::string const& id);
}

#endif //__COLLADA_H__
