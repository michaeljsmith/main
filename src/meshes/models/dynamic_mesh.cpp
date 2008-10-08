#include "dynamic_mesh.h"

meshes::models::dynamic_mesh::dynamic_mesh(format const& fmt)
: fmt(fmt)
{
	this->vertex_strms.resize(this->fmt.vertex_strms.size());
}

int meshes::models::get_vertex_stream_count(dynamic_mesh const& msh)
{
	return int(msh.vertex_strms.size());
}

int meshes::models::get_vertex_stream_stride(dynamic_mesh const& msh, int vertex_stream)
{
	return msh.fmt.vertex_strms[vertex_stream].size;
}

void meshes::models::set_vertex_stream_size(dynamic_mesh& msh, int stream_idx, int size)
{
	msh.vertex_strms[stream_idx].data.resize(size * msh.fmt.vertex_strms[stream_idx].size);
}

int meshes::models::get_vertex_stream_size(dynamic_mesh const& msh, int stream_idx)
{
	return int(msh.vertex_strms[stream_idx].data.size()) / msh.fmt.vertex_strms[stream_idx].size;
}

void meshes::models::set_subset_count(dynamic_mesh& msh, int subset_count)
{
	msh.sbsts.resize(subset_count);
}

int meshes::models::get_subset_count(dynamic_mesh const& msh)
{
	return int(msh.sbsts.size());
}

int meshes::models::get_subset_data_stride(dynamic_mesh const& msh)
{
	return msh.fmt.per_subset_fmt.size;
}

int meshes::models::get_subset_polygon_count(dynamic_mesh const& msh, int subset_index)
{
	int polygon_count;
	switch (msh.sbsts[subset_index].prmtv)
	{
		case primitive_triangles: polygon_count = int(msh.sbsts[subset_index].indices.size()) / 3; break;
		case primitive_polygons: polygon_count = int(msh.sbsts[subset_index].polygon_sizes.size()); break;
		default: polygon_count = -1;
	}	
	return polygon_count;
}

int meshes::models::get_polygon_data_stride(dynamic_mesh const& msh)
{
	return msh.fmt.per_polygon_fmt.size;
}

void meshes::models::set_index_count(dynamic_mesh& msh, int subset_idx, int index_cnt)
{
	msh.sbsts[subset_idx].indices.resize(index_cnt);
}

int meshes::models::get_index_count(dynamic_mesh const& msh, int subset_idx)
{
	return int(msh.sbsts[subset_idx].indices.size());
}

int const* meshes::models::get_indices(dynamic_mesh const& msh, int subset_idx)
{
	return &msh.sbsts[subset_idx].indices[0];
}

int* meshes::models::get_indices(dynamic_mesh& msh, int subset_idx)
{
	return &msh.sbsts[subset_idx].indices[0];
}
