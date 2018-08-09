#ifndef _FONT_H__
#define _FONT_H__
#include <d3dx9.h>
#include <d3d9.h>

class Font
{
private:
	ID3DXFont* _font;
	static Font* pFont;
public:
	Font();
	void Innit();
	void Render(LPD3DXSPRITE sprite, char* str, RECT rect, DWORD dword, D3DXCOLOR color);
	static Font* GetFont();
	~Font();
};
#endif // !_FONT_H__



