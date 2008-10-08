#ifndef __MESH_H__
#define __MESH_H__

#include "maths/maths3d/vector.h"
#include "types/static_instance.h"
#include "types/integer.h"

namespace meshes
{
	enum vertex_data_type
	{
		vertex_data_position,
		vertex_data_normal,

		vertex_data_count
	};

	template <vertex_data_type T> struct vertex_data_specifier {};

	template <vertex_data_type T> struct vertex_data_type_of {};

#define DECLARE_VERTEX_DATA(type_name, name, field_type) \
	namespace {vertex_data_specifier<type_name>& name = static_instance<vertex_data_specifier<type_name> >();} \
	template <> struct vertex_data_type_of<type_name> {typedef field_type type;};

	DECLARE_VERTEX_DATA(vertex_data_position, vertex_position, maths::vector4)
	DECLARE_VERTEX_DATA(vertex_data_normal, vertex_normal, maths::vector4)
#undef DECLARE_VERTEX_DATA

	enum primitive_type
	{
		primitive_triangles,
		primitive_polygons
	};

	enum polygon_data_type
	{
		polygon_data_material,
		polygon_data_smoothing_group,

		polygon_data_count
	};

	template <polygon_data_type T> struct polygon_data_specifier {};

	template <polygon_data_type T> struct polygon_data_type_of {};

#define DECLARE_STATIC_POLYGON_SPECIFIER(type_name, name, field_type) \
	namespace {polygon_data_specifier<type_name>& name = static_instance<polygon_data_specifier<type_name> >();} \
	template <> struct polygon_data_type_of<type_name> {typedef field_type type;};

	DECLARE_STATIC_POLYGON_SPECIFIER(polygon_data_material, polygon_material, int)
	DECLARE_STATIC_POLYGON_SPECIFIER(polygon_data_smoothing_group, polygon_smoothing_group, u32)
#undef DECLARE_STATIC_POLYOGN_SPECIFIER

	template <typename T> struct index_type_of {};
}

#endif //__MESH_H__
