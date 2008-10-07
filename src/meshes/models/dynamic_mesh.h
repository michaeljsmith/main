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
			std::vector<int> indices;
			std::vector<char> data;
			std::vector<char> polygon_data;
		};

		dynamic_mesh(format const& fmt);

		format fmt;
		std::vector<vertex_stream> vertex_strms;
		std::vector<polygon_subset> sbsts;
	};
}}

namespace meshes
{
	using models::dynamic_mesh;
}

#endif //__DYNAMIC_MESH_H__
