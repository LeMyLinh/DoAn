#ifndef _CTEXT_H_
#define _CTEXT_H_
#include <d3dx9.h>


class CText
{
private:
	LPD3DXFONT m_font;
	int m_fontSize;
	RECT Region;
	int Localtime;
	bool isDrawAnimation;
	D3DCOLOR Color;
public:
	char *Text;
	CText(char* text, int size, float x, float y,D3DCOLOR color);
	virtual ~CText(void);
	void Draw();
	void Init();
	void renderAnimation(int deltaTime_);
	void SetText(char* text);
};
#endif
