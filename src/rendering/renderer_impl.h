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
		virtual void begin_render();
		virtual void end_render();

	private:
		renderer rndr;
	};
}

template <typename T> void rendering::renderer_impl<T>::begin_render()
{
	begin_render(this->rndr);
}

template <typename T> void rendering::renderer_impl<T>::end_render()
{
	end_render(this->rndr);
}

#endif //__RENDERER_IMPL_H__
