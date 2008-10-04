#include "renderer_dx9.h"

void rendering::set_device(renderer_dx9& rndr, IDirect3DDevice9* device)
{
	rndr.device = device;
}
