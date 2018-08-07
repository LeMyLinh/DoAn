#include "SmallCandle.h"


SmallCandle* SmallCandle::pStaticObj = 0;


SmallCandle::SmallCandle()
{
}

void SmallCandle::Init()
{
	BaseObject::LoadResource(L"Resources/ground/1.png", 2, 1, 0);
}

SmallCandle * SmallCandle::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new SmallCandle();
	return pStaticObj;
}

void SmallCandle::Update()
{
	Sprite->Next();
}

void SmallCandle::Draw(int _x, int _y)
{
	Sprite->Draw(_x + Sprite->_FrameWidth / 2, _y + Sprite->_FrameHeight / 2);
}


SmallCandle::~SmallCandle()
{
}
