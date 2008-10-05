#include "vector.h"

#include <cmath>

float maths::vectors::archetypes::dot(vector4 const& v1, vector4 const& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

float maths::vectors::archetypes::magnitude_sqr(vector4 const& v)
{
	return dot(v, v);
}

float maths::vectors::archetypes::magnitude(vector4 const& v)
{
	return std::sqrt(magnitude_sqr(v));
}

void maths::vectors::archetypes::cross(vector4& vo, vector4 const& v1, vector4 const& v2)
{
	vo.x = + v1.y * v2.z - v1.z * v2.y;
	vo.y = - v1.x * v2.z + v1.z * v2.x;
	vo.z = + v1.x * v2.y - v1.y * v2.x;
	vo.w = 1.0f;
}

void maths::vectors::archetypes::copy(vector4& vo, vector4 const& vi)
{
	vo.x = vi.x; vo.y = vi.y; vo.z = vi.z; vo.w = vi.w;
}

void maths::vectors::archetypes::add(vector4& vo, vector4 const& vi)
{
	vo.x += vi.x; vo.y += vi.y; vo.z += vi.z;
}

void maths::vectors::archetypes::add_copy(vector4& vo, vector4 const& v1, vector4 const& v2)
{
	vo.x = v1.x + v2.x; vo.y = v1.y + v2.y; vo.z = v1.z + v2.z; vo.w = 1.0f;
}

void maths::vectors::archetypes::subtract(vector4& vo, vector4 const& vi)
{
	vo.x -= vi.x; vo.y -= vi.y; vo.z -= vi.z;
}

void maths::vectors::archetypes::subtract_copy(vector4& vo, vector4 const& v1, vector4 const& v2)
{
	vo.x = v1.x - v2.x; vo.y = v1.y - v2.y; vo.z = v1.z - v2.z; vo.w = 1.0f;
}

void maths::vectors::archetypes::scale(vector4& v, float s)
{
	v.x *= s; v.y *= s; v.z *= s;
}

void maths::vectors::archetypes::scale_copy(vector4& vo, vector4 const& vi, float s)
{
	vo.x = vi.x * s;
	vo.y = vi.y * s;
	vo.z = vi.z * s;
	vo.w = vi.w;
}
