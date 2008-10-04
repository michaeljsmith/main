#ifndef __RENDERER_IMPL_H__
#define __RENDERER_IMPL_H__

#include "renderer.h"

namespace rendering
{
	template <typename T> class renderer_impl : public renderer
	{
	public:
		typedef T renderer;

		// renderer
		virtual void begin();
		virtual void end();

		renderer rndr;
	};

	template <typename T> T& get_renderer(renderer_impl<T>& impl);
}

template <typename T> void rendering::renderer_impl<T>::begin()
{
	begin_render(this->rndr);
}

template <typename T> void rendering::renderer_impl<T>::end()
{
	end_render(this->rndr);
}

template <typename T> T& rendering::get_renderer(rendering::renderer_impl<T>& impl)
{
	return impl.rndr;
}

#endif //__RENDERER_IMPL_H__
