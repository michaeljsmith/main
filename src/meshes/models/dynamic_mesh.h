#ifndef __DYNAMIC_MESH_H__
#define __DYNAMIC_MESH_H__

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

		class vertex_stream
		{
		public:
			vertex_format format;
			std::vector<char> data;
		};

		int stream_indices[vertex_data_count];
		std::vector<vertex_stream> vertex_streams;

		dynamic_mesh() {std::fill(this->stream_indices, this->stream_indices + vertex_data_count, -1);
	};
}}

namespace meshes
{
	using models::dynamic_mesh;
}

#endif //__DYNAMIC_MESH_H__
