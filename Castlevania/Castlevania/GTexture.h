#ifndef _GTEXTTURE_H_
#define _GTEXTTURE_H_
#include <d3dx9.h>
#include <d3d9.h>

class GTexture
{
private:
	LPDIRECT3DTEXTURE9 Texture;
	RECT srcRect;
	//D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	float angle;
	float deep;
	D3DCOLOR color;
public:
	int Width;
	int Height;
	GTexture();
	GTexture(const GTexture &cTexture);
	void loadTextTureFromFile(LPCWSTR fileName, D3DXCOLOR ColorKey = 0xffffffff);
	//in texture voi position trung voi tam .
	void RenderTexture(int x, int y);
	void RenderTexture(int x, int y, RECT srcRect);
	//cai dat thuoc tinh mac dinh.
	void SetDefaul();
	//chinh sua thuoc tinh (xoay, zoom, flip).
	void SetFormat(D3DXVECTOR2 scale,
		float angle,
		float deep,
		D3DCOLOR color = 0xffffffff);
	void SetColor(D3DCOLOR _color = 0xffffffff);
	~GTexture();
};

#endif // _GTEXTTURE_H_


