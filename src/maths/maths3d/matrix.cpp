#include "matrix.h"

void maths::matrices::archetypes::multiply(matrix44_RM& mo, matrix44_RM const& m1, matrix44_RM const& m2)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mo.m[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k)
				mo.m[i][j] += m1.m[i][k] * m2.m[k][j];
		}
	}
}

void maths::matrices::archetypes::multiply(vector4& vo, vector4 const& vi, matrix44_RM const& m)
{
	for (int j = 0; j < 4; ++j)
	{
		vo[j] = 0.0f;
		for (int k = 0; k < 4; ++k)
			vo[j] += vi[k] * m.m[k][j];
	}
}

void maths::matrices::archetypes::scale(matrix44_RM& m, float s)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			m.m[i][j] *= s;
	}
}

void maths::matrices::archetypes::scale_copy(matrix44_RM& mo, matrix44_RM const& mi, float s)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			mo.m[i][j] = mi.m[i][j] * s;
	}
}
