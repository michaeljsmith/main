#ifndef __MESH_H__
#define __MESH_H__

#include "types/static_instance.h"

namespace meshes
{
	enum vertex_data_type
	{
		vertex_data_position,
		vertex_data_normal,

		vertex_data_count
	};

	template <vertex_data_type> struct vertex_data_specifier {};

#define DECLARE_STATIC_VERTEX_SPECIFIER(type, name) namespace {vertex_data_specifier<type>& name = static_instance<type>()}
	DECLARE_STATIC_VERTEX_SPECIFIER(vertex_data_position, vertex_position)
	DECLARE_STATIC_VERTEX_SPECIFIER(vertex_data_normal, vertex_normal)
#undef DECLARE_STATIC_VERTEX_SPECIFIER
}

#endif //__MESH_H__
