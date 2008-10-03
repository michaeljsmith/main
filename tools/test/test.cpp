#include <boost/shared_ptr.hpp>

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

	return 0;
}
