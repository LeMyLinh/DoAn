#include "Bat.h"



Bat::Bat()
{
}

Bat::Bat(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	startIndex = 1;
	index = 0;
	endIndex = 3;
	vecY = 0;
	turn = 1;
	//Infomation
	HP = 1;
	Damage = 2;
	Point = 200;
	temp = index;
	IsFight = false;

}

void Bat::Update(Box RectCamera, Box simon, int Deltatime)
{
	Enemy::Update(RectCamera, simon, Deltatime);
	if (!IsFight)
	{
		if (x < simon.x)
		{
			direction = 1;
		}
		else
			direction = -1;
		if (Collision::AABBCheck(GetBoundBox(), simon))
		{
			IsFight = true;
		}
	}
	else
	{
		UpdateSprite();
		vecX = 4 * direction;
		turn = direction;
		//update position
		if (y < simon.y + simon.h - 30)
		{
			vecY = 2;
		}
		else if (y > simon.y + simon.h - 25)
		{
			vecY = -2;
		}
		else
			vecY = 0;

		x += vecX;
		y += vecY;
	}
}

void Bat::UpdateSprite()
{
	temp += 0.4;
	index = (int)temp;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		temp = startIndex;
	}
}

void Bat::Draw()
{
	EnemyRender::GetStaticObj()->DrawBat(x, y, index, turn);
}

Box Bat::GetBoundBox()
{
	Box r = this->GetBox();
	r.x = x - 220;
	r.w = 440;
	r.h = 100;
	return r;
}


Bat::~Bat()
{
}
