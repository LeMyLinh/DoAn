#include "BigCandel.h"


BigCandel* BigCandel::pStaticObj = 0;


BigCandel::BigCandel()
{
}

void BigCandel::Init()
{
	BaseObject::LoadResource(L"Resources/ground/0.png", 2, 1, 0);
}

BigCandel * BigCandel::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new BigCandel();
	return pStaticObj;
}

void BigCandel::Update()
{
	Sprite->Next();
}

void BigCandel::Draw(int _x, int _y)
{
	Sprite->Draw(_x + Sprite->_FrameWidth / 2, _y + Sprite->_FrameHeight / 2);
}


BigCandel::~BigCandel()
{
}
