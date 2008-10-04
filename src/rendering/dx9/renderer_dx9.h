#ifndef __RENDERER_DX9__
#define __RENDERER_DX9__

#include <d3d9.h>

namespace rendering
{
	class renderer_dx9
	{
	public:
		renderer_dx9(): device(0) {}
		IDirect3DDevice9* device;
	};

	void set_device(renderer_dx9& rndr, IDirect3DDevice9* device);
	void begin_render(renderer_dx9& rndr);
	void end_render(renderer_dx9& rndr);
}

#endif //__RENDERER_DX9__
