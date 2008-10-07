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

	template <vertex_data_type T> struct vertex_data_specifier {};

#define DECLARE_STATIC_VERTEX_SPECIFIER(type, name) namespace {vertex_data_specifier<type>& name = static_instance<vertex_data_specifier<type> >();}
	DECLARE_STATIC_VERTEX_SPECIFIER(vertex_data_position, vertex_position)
	DECLARE_STATIC_VERTEX_SPECIFIER(vertex_data_normal, vertex_normal)
#undef DECLARE_STATIC_VERTEX_SPECIFIER

	enum primitive_type
	{
		primitive_triangles,
		primitive_polygon
	};

	enum polygon_data_type
	{
		polygon_data_material,
		polygon_data_smoothing_group,

		polygon_data_count
	};

	template <polygon_data_type T> struct polygon_data_specifier {};

#define DECLARE_STATIC_POLYGON_SPECIFIER(type, name) namespace {polygon_data_specifier<type>& name = static_instance<polygon_data_specifier<type> >();}
	DECLARE_STATIC_POLYGON_SPECIFIER(polygon_data_material, polygon_material)
	DECLARE_STATIC_POLYGON_SPECIFIER(polygon_data_smoothing_group, polygon_smoothing_group)
#undef DECLARE_STATIC_POLYOGN_SPECIFIER
}

#endif //__MESH_H__
