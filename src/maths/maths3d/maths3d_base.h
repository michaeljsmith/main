#ifndef __MATHS3D_H__
#define __MATHS3D_H__

namespace maths
{
	template <typename T> struct archetype_of {};

	template <typename T1, typename T2> inline float dot(T1 const& v1, T2 const& v2);
	template <typename T1> inline float magnitude_sqr(T1 const& v);
	template <typename T1> inline float magnitude(T1 const& v);
	template <typename T1, typename T2, typename T3> inline void cross(T1& vo, T2 const& v1, T3 const& v2);
	template <typename T1, typename T2> inline void copy(T1& vo, T2 const& vi);
	template <typename T1, typename T2> inline void add(T1& vo, T2 const& vi);
	template <typename T1, typename T2, typename T3> inline void add_copy(T1& vo, T2 const& v1, T3 const& v2);
	template <typename T1, typename T2> inline void subtract(T1& vo, T2 const& vi);
	template <typename T1, typename T2, typename T3> inline void subtract_copy(T1& vo, T2 const& v1, T3 const& v2);
	template <typename T1> inline void scale(T1& v, float s);
	template <typename T1, typename T2> inline void scale_copy(T1& vo, T2 const& vi, float s);
	template <typename T1, typename T2, typename T3> inline void multiply(T1& vo, T2 const& v1, T3 const& v2);

	template <typename T> inline typename archetype_of<T>::type& to_archetype(T& v) {return *reinterpret_cast<typename archetype_of<T>::type*>(&v);}
	template <typename T> inline typename archetype_of<T>::type const& to_archetype(T const& v) {return *reinterpret_cast<typename archetype_of<T>::type const*>(&v);}

	template <typename T1, typename T2> inline T1 operator^(T1 const& v1, T2 const& v2);
	template <typename T1, typename T2> inline T1& operator+=(T1& vo, T2 const& vi);
	template <typename T1, typename T2> inline T1 operator+(T1 const& v1, T2 const& v2);
	template <typename T1, typename T2> inline T1& operator-=(T1& vo, T2 const& vi);
	template <typename T1, typename T2> inline T1 operator-(T1 const& v1, T2 const& v2);
	template <typename T1> inline T1& operator*=(T1& v, float s);
	template <typename T1, typename T2> inline T1 operator*(T1 const& v1, T2 const& v2);
	template <typename T1> inline T1 operator*(T1 const& vi, float s);
	template <typename T1> inline T1 operator*(float s, T1 const& vi);
}

template <typename T1, typename T2> inline float maths::dot(T1 const& v1, T2 const& v2)
{
	dot(to_archetype(v1), to_archetype(v2));
}

template <typename T1> inline float maths::magnitude_sqr(T1 const& v)
{
	magnitude_sqr(to_archetype(v));
}

template <typename T1> inline float maths::magnitude(T1 const& v)
{
	magnitude(to_archetype(v));
}

template <typename T1, typename T2, typename T3> inline void maths::cross(T1& vo, T2 const& v1, T3 const& v2)
{
	cross(to_archetype(vo), to_archetype(v1), to_archetype(v2));
}

template <typename T1, typename T2> inline void maths::copy(T1& vo, T2 const& vi)
{
	copy(to_archetype(vo), to_archetype(vi));
}

template <typename T1, typename T2> inline void maths::add(T1& vo, T2 const& vi)
{
	add(to_archetype(vo), to_archetype(vi));
}

template <typename T1, typename T2, typename T3> inline void maths::add_copy(T1& vo, T2 const& v1, T3 const& v2)
{
	add_copy(to_archetype(vo), to_archetype(v1), to_archetype(v2));
}

template <typename T1, typename T2> inline void maths::subtract(T1& vo, T2 const& vi)
{
	subtract(to_archetype(vo), to_archetype(vi));
}

template <typename T1, typename T2, typename T3> inline void maths::subtract_copy(T1& vo, T2 const& v1, T3 const& v2)
{
	subtract_copy(to_archetype(vo), to_archetype(v1), to_archetype(v2));
}

template <typename T1> inline void maths::scale(T1& v, float s)
{
	scale(to_archetype(v), s);
}

template <typename T1, typename T2> inline void maths::scale_copy(T1& vo, T2 const& vi, float s)
{
	scale_copy(to_archetype(vo), to_archetype(vi), to_archetype(s));
}

template <typename T1, typename T2, typename T3> inline void maths::multiply(T1& vo, T2 const& v1, T3 const& v2)
{
	multiply(to_archetype(vo), to_archetype(v1), to_archetype(v2));
}

template <typename T1, typename T2> inline T1 maths::operator^(T1 const& v1, T2 const& v2)
{
	T1 result;
	cross(result, v1, v2);
	return result;
}

template <typename T1, typename T2> inline T1& maths::operator+=(T1& vo, T2 const& vi)
{
	add(vo, vi);
	return vo;
}

template <typename T1, typename T2> inline T1 maths::operator+(T1 const& v1, T2 const& v2)
{
	T1 result;
	add_copy(result, v1, v2);
	return result;
}

template <typename T1, typename T2> inline T1& maths::operator-=(T1& vo, T2 const& vi)
{
	subtract(vo, vi);
	return vo;
}

template <typename T1, typename T2> inline T1 maths::operator-(T1 const& v1, T2 const& v2)
{
	T1 result;
	subtract_copy(result, v1, v2);
	return result;
}

template <typename T1> inline T1& maths::operator*=(T1& v, float s)
{
	scale(v, s);
	return v;
}

template <typename T1, typename T2> inline T1 maths::operator*(T1 const& v1, T2 const& v2)
{
	T1 result;
	multiply(result, v1, v2);
	return result;
}

template <typename T1> inline T1 maths::operator*(T1 const& vi, float s)
{
	T1 result;
	scale_copy(result, vi, s);
	resturn result;
}

template <typename T1> inline T1 maths::operator*(float s, T1 const& vi)
{
	T1 result;
	scale_copy(result, vi, s);
	resturn result;
}

#endif //__MATHS3D_H__
