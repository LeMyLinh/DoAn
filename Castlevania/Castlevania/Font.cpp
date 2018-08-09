#include "Font.h"
#include <algorithm>
#include "Global.h"

Font* Font::pFont = 0;

Font::Font()
{

}

void Font::Innit()
{
	// create font
	_font = NULL;
	HRESULT hr = D3DXCreateFontA(G_lpDirect3DDevice, 30, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Arial", &_font);
	if (SUCCEEDED(hr))
		return;
}

void Font::Render(LPD3DXSPRITE sprite, char * str, RECT rect, DWORD dword, D3DXCOLOR color)
{
	if (_font)
	{
		_font->DrawTextA(sprite, str, -1, &rect, dword, color);
	}
}

Font* Font::GetFont()
{
	if (pFont == NULL)
	{
		pFont = new Font();
	}
	return pFont;
}


Font::~Font()
{
}
