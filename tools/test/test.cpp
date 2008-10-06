#include <boost/shared_ptr.hpp>
#include "maths/maths3d/vector.h"
#include "maths/maths3d/matrix.h"

class iface1
{
	virtual void destroy() = 0;
};

class iface2
{
	virtual void destroy() = 0;
};

class ifaces : public iface1, public iface2
{
};

template <typename B> class impl : public B
{
	virtual void destroy() {}
};

class foo : public impl<ifaces>
{
	virtual void destroy() {}
};

int main()
{
	foo f;

	maths::vector4 v1, v2;
	maths::vector4 v3;
	v3 = v1 + v2;
	v3 += v3;
	v3 *= 2.0f;

	maths::matrix44 m;
	v3 = v3 * m;

	return 0;
}
