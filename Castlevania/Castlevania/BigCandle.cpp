#include "BigCandle.h"
#include "Constant.h"

BigCandle* BigCandle::pStaticObj = 0;

BigCandle::BigCandle()
{
}

BigCandle::~BigCandle()
{
}

void BigCandle::Init()
{
	BaseObject::LoadResource(BIGCANDLE_IMAGE, COL_OF_CANDLE_SPRITE, ROW_OF_CANDLE_SPRITE, 0);
}

BigCandle * BigCandle::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new BigCandle();
	return pStaticObj;
}

void BigCandle::Update()
{
	Sprite->Next();
}

void BigCandle::Draw(int _x, int _y)
{
	Sprite->Draw(_x + Sprite->_FrameWidth / 2, _y + Sprite->_FrameHeight / 2);
}
