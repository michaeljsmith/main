#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "maths3d_base.h"
#include "vector.h"

namespace maths {namespace matrices {namespace archetypes
{
	using vectors::archetypes::vector4;

	class matrix44_RM
	{
	public:
		float m[4][4];
	};

	void multiply(matrix44_RM& mo, matrix44_RM const& m1, matrix44_RM const& m2);
	void multiply(vector4& vo, vector4 const& vi, matrix44_RM const& m);
	void scale(matrix44_RM& m, float s);
	void scale_copy(matrix44_RM& mo, matrix44_RM const& mi, float s);
}}}

namespace maths {namespace matrices
{
	class matrix44
	{
	public:
		float m[4][4];
	};
}}

namespace maths
{
	using matrices::matrix44;

	template <> struct archetype_of<matrix44> {typedef matrices::archetypes::matrix44_RM type;};
}

#endif //__MATRIX_H__
