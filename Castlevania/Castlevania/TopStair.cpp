#include "TopStair.h"

TopStair* TopStair::pStaticObj = 0;


TopStair::TopStair()
{
}

void TopStair::Init()
{
	BaseObject::LoadResource(L"Resources/ground/4-3.png", 1, 1, 0);
}

TopStair * TopStair::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new TopStair();
	return pStaticObj;
}

void TopStair::Draw(int _x, int _y)
{
	Sprite->Draw(_x + Sprite->_FrameWidth / 2, _y + Sprite->_FrameHeight / 2);
}


TopStair::~TopStair()
{
}
