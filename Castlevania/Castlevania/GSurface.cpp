#include "GSurface.h"
#include "Global.h"



GSurface::GSurface()
{
}

int GSurface::LoadSurfaceFromFile(char * filePath)
{
	HRESULT result = D3DXGetImageInfoFromFileA(filePath, &info);

	if (result != D3D_OK)
	{
		return NULL;
	}

	G_lpDirect3DDevice->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFileA(
		surface,
		NULL,
		NULL,
		filePath,
		NULL,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		NULL);

	if (result != D3D_OK)
	{
		return NULL;
	}
	return 1;
}

void GSurface::DrawSurface()
{
	G_lpDirect3DDevice->StretchRect(surface, NULL, G_BackBuffer, NULL, D3DTEXF_NONE);
}


void GSurface::DrawSurface(RECT sourceRect, RECT destRect)
{
	G_lpDirect3DDevice->StretchRect(surface, &sourceRect, G_BackBuffer, &destRect, D3DTEXF_NONE);
}

LPDIRECT3DSURFACE9 GSurface::GetSurFace()
{
	return surface;
}



GSurface::~GSurface()
{
	if(surface!=NULL) surface->Release();
}
