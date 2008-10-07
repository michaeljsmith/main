#include "dynamic_mesh.h"

meshes::models::dynamic_mesh::dynamic_mesh(format const& fmt)
: fmt(fmt)
{
	this->vertex_strms.resize(this->fmt.vertex_strms.size());
}
