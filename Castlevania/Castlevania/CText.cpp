#include "CText.h"
#include "Global.h"

CText::CText(char* text, int size, float x, float y,D3DCOLOR color)
{
	Text = new char[strlen(text)];
	strcpy_s(Text,strlen(Text),text);
	m_fontSize = size;
	Region.left=x;
	Region.top=y;
	Region.right=G_ScreenWidth;
	Region.bottom=G_ScreenHeight;
	Color=color;
	Init();
}
void CText::Init()
{
	D3DXFONT_DESC FontDesc = {
		m_fontSize,
		0,
		400,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH, L"GameSystem" };

	//create font
	D3DXCreateFontIndirect(G_lpDirect3DDevice, &FontDesc, &m_font);
	Localtime = 0;
	isDrawAnimation=false;
}
void CText::Draw()
{
	m_font->DrawTextA(NULL,
		Text,
		-1,
		&Region,
		NULL,
		Color);
}
void CText::renderAnimation(int deltaTime_)
{
	Localtime += deltaTime_;
	if (Localtime >= 50)
	{
		Localtime = 0;
		isDrawAnimation=!isDrawAnimation;
	}
	if (this->isDrawAnimation) Draw();

}
void CText::SetText(char* text)
{
	Text=text;
}
CText::~CText(void)
{
	if(m_font != NULL)
	{
		m_font->Release(); //release font
		m_font = NULL;
	}
}
