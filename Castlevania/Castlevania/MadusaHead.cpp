#include "MadusaHead.h"

MadusaHead::MadusaHead()
{
	
}

MadusaHead::MadusaHead(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	
	startIndex = 1;
	index = 0;
	endIndex = 1;
	vecY = 0;
	turn = 1;
	//Infomation
	HP = 1;
	Damege = 2;
	Point = 200;
	temp = index;
	IsFight = false;
	delay = 0;
	localTime = 0;
	
	y -= 64;
}

void MadusaHead::Update(Box RectCamera, Box simon, int Deltatime)
{
	double pi = acos(-1);
	Enemy::Update(RectCamera, simon, Deltatime);

	localTime += Deltatime;
	if (localTime < delay)
		return;
	else
	{
		localTime = 0;
		delay = 0;
	}

	if (!IsFight)
	{
		/*if (simon.x < x - 96)
			return;*/
		srand(time(0));
		int r0 = rand() % 2;
		turn *= (1 - 2 * r0);
		IsFight = true;
		if (turn == 1)
		{
			x = RectCamera.x - 30;
			angle = 90;
		}
		else
		{
			x = RectCamera.x + RectCamera.w;
			angle = 90;
		}
		y = simon.y;

	}
	else
	{
		if (Collision::AABBCheck(this->GetBox(), RectCamera) == false)
		{
			IsFight = false;
			delay = 500;
		}
		vecX = 3.5 * turn;
		angle += 5;
		if (angle > 360)
			angle = 0;
		vecY = sinf(angle * pi / 180) * 7.6;
		x += vecX;
		y += vecY;
	}
	UpdateSprite();
}

void MadusaHead::UpdateSprite()
{
	temp += 0.1;
	index = (int)temp;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		temp = startIndex;
	}
}

Box MadusaHead::GetBoundBox(Box RectCamera)
{
	Box r;
	r.y = RectCamera.y;
	r.x = x - 96;
	r.w = RectCamera.w -(x - 96-RectCamera.x);
	r.h = RectCamera.h;
	return r;
}


MadusaHead::~MadusaHead()
{	
}
