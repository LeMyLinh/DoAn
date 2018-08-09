#include "Stair.h"

Stair* Stair::pStaticObj = 0;


void Stair::Init()
{
	BaseObject::LoadResource(L"Resources/ground/3-3.png", 1, 1, 0);
}


Stair* Stair::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new Stair();
	return pStaticObj;
}

void Stair::Draw(int _x, int _y)
{
	Sprite->Draw(_x + Sprite->_FrameWidth / 2, _y + Sprite->_FrameHeight / 2);
}


Stair::Stair()
{
}


Stair::~Stair()
{
}
