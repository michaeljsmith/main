#include "renderer_dx9.h"
#include "DXUT.h"

void rendering::set_device(renderer_dx9& rndr, IDirect3DDevice9* device)
{
	rndr.device = device;
}

void rendering::begin_render(renderer_dx9& rndr)
{
	HRESULT hr;

	// Clear the render target and the zbuffer 
	V( rndr.device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

	// Render the scene
	V( SUCCEEDED( rndr.device->BeginScene() ) );
}

void rendering::end_render(renderer_dx9& rndr)
{
	HRESULT hr;

	V( rndr.device->EndScene() );
}
