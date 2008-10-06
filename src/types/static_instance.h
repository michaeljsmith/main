#ifndef __STATIC_INSTANCE_H__
#define __STATIC_INSTANCE_H__

template <typename T> inline T& static_instance()
{
	static T instance;
	return instance;
}

#endif //__STATIC_INSTANCE_H__
