#ifndef __DYNAMIC_MESH_H__
#define __DYNAMIC_MESH_H__

#include "../mesh.h"
#include <vector>
#include <algorithm>

namespace meshes {namespace models
{
	class dynamic_mesh
	{
	public:
		class vertex_format
		{
		public:
			vertex_format(): size(0) {std::fill(this->offsets, this->offsets + vertex_data_count, -1);}
			int offsets[vertex_data_count];
			int size;
		};

		class polygon_format
		{
		public:
			polygon_format(): size(0) {std::fill(this->offsets, this->offsets + polygon_data_count, -1);}
			int offsets[polygon_data_count];
			int size;
		};

		class format
		{
		public:
			format() {std::fill(this->stream_indcs, this->stream_indcs+ vertex_data_count, -1);}

			int stream_indcs[vertex_data_count];
			std::vector<vertex_format> vertex_strms;
			polygon_format per_subset_fmt;
			polygon_format per_polygon_fmt;
		};

		class vertex_stream
		{
		public:
			std::vector<char> data;
		};

		class polygon_subset
		{
		public:
			polygon_subset(): prmtv(primitive_triangles) {}
			primitive_type prmtv;
			std::vector<int> indices;
			std::vector<char> polygon_data;
			std::vector<int> polygon_sizes;
		};

		dynamic_mesh(format const& fmt);

		format fmt;
		std::vector<vertex_stream> vertex_strms;
		std::vector<polygon_subset> sbsts;
		std::vector<char> subset_data;
	};

	template <typename T> struct index_type_of {typedef int type;};

	template <polygon_data_type D> inline int find_vertex_stream_for_data(dynamic_mesh const& mesh, polygon_data_specifier<D> const& /*specifier*/);
	int get_vertex_stream_count(dynamic_mesh const& msh);
	int get_vertex_stream_stride(dynamic_mesh const& msh, int stream_idx);
	void set_vertex_stream_size(dynamic_mesh& msh, int stream_idx, int size);
	int get_vertex_stream_size(dynamic_mesh const& msh, int vertex_stream);
	template <vertex_data_type D> inline typename vertex_data_type_of<D>::type const* get_vertex_data_buffer(dynamic_mesh const& msh, int stream_idx, vertex_data_specifier<D> const& /*specifier*/);
	template <vertex_data_type D> inline typename vertex_data_type_of<D>::type* get_vertex_data_buffer(dynamic_mesh& msh, int stream_idx, vertex_data_specifier<D> const& /*specifier*/);
	void set_subset_count(dynamic_mesh& msh, int subset_count);
	int get_subset_count(dynamic_mesh const& msh);
	template <polygon_data_type D> inline typename polygon_data_type_of<D>::type const* get_subset_data_buffer(dynamic_mesh const& msh, polygon_data_specifier<D> const& /*specifier*/);
	template <polygon_data_type D> inline typename polygon_data_type_of<D>::type* get_subset_data_buffer(dynamic_mesh& msh, polygon_data_specifier<D> const& /*specifier*/);
	int get_subset_data_stride(dynamic_mesh const& msh);
	template <polygon_data_type D> inline typename polygon_data_type_of<D>::type const* get_polygon_data_buffer(dynamic_mesh const& msh, int subset_index, polygon_data_specifier<D> const& /*specifier*/);
	template <polygon_data_type D> inline typename polygon_data_type_of<D>::type* get_polygon_data_buffer(dynamic_mesh& msh, int subset_index, polygon_data_specifier<D> const& /*specifier*/);
	int get_subset_polygon_count(dynamic_mesh const& msh, int subset_index);
	int get_polygon_data_stride(dynamic_mesh const& msh);
	void set_index_count(dynamic_mesh& msh, int subset_idx, int index_cnt);
	int get_index_count(dynamic_mesh const& msh, int subset_idx);
	int const* get_indices(dynamic_mesh const& msh, int subset_idx);
	int* get_indices(dynamic_mesh& msh, int subset_idx);
}}

namespace meshes
{
	using models::dynamic_mesh;
}

template <meshes::polygon_data_type D> inline int meshes::models::find_vertex_stream_for_data(dynamic_mesh const& msh, polygon_data_specifier<D> const& /*specifier*/)
{
	return msh.fmt.stream_indcs[D];
}

template <meshes::vertex_data_type D> inline typename meshes::vertex_data_type_of<D>::type const* meshes::models::get_vertex_data_buffer(dynamic_mesh const& msh, int stream_idx, vertex_data_specifier<D> const& /*specifier*/)
{
	int offset = msh.fmt.vertex_strms[stream_idx].offsets[D];
	return reinterpret_cast<typename vertex_data_type_of<D>::type const*>(&msh.vertex_strms[stream_idx].data[offset]);
}

template <meshes::vertex_data_type D> inline typename meshes::vertex_data_type_of<D>::type* meshes::models::get_vertex_data_buffer(dynamic_mesh& msh, int stream_idx, vertex_data_specifier<D> const& /*specifier*/)
{
	int offset = msh.fmt.vertex_strms[stream_idx].offsets[D];
	return reinterpret_cast<typename vertex_data_type_of<D>::type*>(&msh.vertex_strms[stream_idx].data[offset]);
}

template <meshes::polygon_data_type D> inline typename meshes::polygon_data_type_of<D>::type const* meshes::models::get_subset_data_buffer(dynamic_mesh const& msh, polygon_data_specifier<D> const& /*specifier*/)
{
	int offset = msh.fmt.per_subset_fmt.offsets[D];
	return reinterpret_cast<typename polygon_data_type_of<D>::type const*>(&msh.subset_data[offset]);
}

template <meshes::polygon_data_type D> inline typename meshes::polygon_data_type_of<D>::type* meshes::models::get_subset_data_buffer(dynamic_mesh& msh, polygon_data_specifier<D> const& /*specifier*/)
{
	int offset = msh.fmt.per_subset_fmt.offsets[D];
	return reinterpret_cast<typename polygon_data_type_of<D>::type*>(&msh.subset_data[offset]);
}

template <meshes::polygon_data_type D> inline typename meshes::polygon_data_type_of<D>::type const* meshes::models::get_polygon_data_buffer(dynamic_mesh const& msh, int subset_index, polygon_data_specifier<D> const& /*specifier*/)
{
	int offset = msh.fmt.per_polygon_fmt.offsets[D];
	return reinterpret_cast<typename polygon_data_type_of<D>::type const*>(&msh.sbsts[subset_idx].polygon_data[offset]);
}

template <meshes::polygon_data_type D> inline typename meshes::polygon_data_type_of<D>::type* meshes::models::get_polygon_data_buffer(dynamic_mesh& msh, int subset_index, polygon_data_specifier<D> const& /*specifier*/)
{
	int offset = msh.fmt.per_polygon_fmt.offsets[D];
	return reinterpret_cast<typename polygon_data_type_of<D>::type*>(&msh.sbsts[subset_idx].polygon_data[offset]);
}

#endif //__DYNAMIC_MESH_H__
