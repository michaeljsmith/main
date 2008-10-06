#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "maths3d_base.h"

namespace maths {namespace vectors {namespace archetypes
{
	class vector4
	{
	public:
		float x, y, z, w;

		float& operator[](int i) {return reinterpret_cast<float*>(this)[i];}
		float operator[](int i) const {return reinterpret_cast<float const*>(this)[i];}
	};

	float dot(vector4 const& v1, vector4 const& v2);
	float magnitude_sqr(vector4 const& v);
	float magnitude(vector4 const& v);
	void cross(vector4& vo, vector4 const& v1, vector4 const& v2);
	void copy(vector4& vo, vector4 const& vi);
	void add(vector4& vo, vector4 const& vi);
	void add_copy(vector4& vo, vector4 const& v1, vector4 const& v2);
	void subtract(vector4& vo, vector4 const& vi);
	void subtract_copy(vector4& vo, vector4 const& v1, vector4 const& v2);
	void scale(vector4& v, float s);
	void scale_copy(vector4& vo, vector4 const& vi, float s);
}}}

namespace maths {namespace vectors
{
	class vector4
	{
	public:
		float x, y, z, w;
	};
}}

namespace maths
{
	using vectors::vector4;

	template <> struct archetype_of<vector4> {typedef vectors::archetypes::vector4 type;};
}

#endif //__VECTOR_H__
