#ifndef _GSURFACE_H_
#define _GSURFACE_H_
#include <d3d9.h>
#include <d3dx9.h>

class GSurface
{
private:
	LPDIRECT3DSURFACE9 surface;
public:
	D3DXIMAGE_INFO info;
	GSurface();
	int LoadSurfaceFromFile(char* filePath);
	void DrawSurface();
	void DrawSurface(RECT rourceRect ,RECT destRect);
	LPDIRECT3DSURFACE9 GetSurFace();
	~GSurface();
};
#endif

