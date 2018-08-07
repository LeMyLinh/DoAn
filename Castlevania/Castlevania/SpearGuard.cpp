#include "SpearGuard.h"





SpearGuard::SpearGuard()
{
}

SpearGuard::SpearGuard(int _id, int _type, int _x, int _y, int _Width, int _Height):Enemy(_id, _type, _x, _y, _Width, _Height)
{
	startIndex = 0;
	index = 0;
	endIndex = 3;
	vecY = 0;
	//gioi han
	bound = 120;
	turn = 1;
	vecX = turn * 1.5;
	xOld = x;
	//Infomation
	HP = 3;
	Damege = 2;
	Point = 400;
	temp = index;
}

void SpearGuard::Update(Box RectCamera,Box simon, int Deltatime)
{	
	Enemy::Update(RectCamera,simon,Deltatime);
	if (delay < 20)
	{
		delay++;
		return;
	}
	int r0;
	UpdateSprite();
	if (vecX > 0)
	{
		if (x >= xOld-bound+30 && x <= xOld - bound + 33)
		{
			srand(time(0));
			r0 = rand() % 2;
			turn *= (1 - 2 * r0);
		}
		
		if (x >= xOld + bound)
		{
			turn *= -1;
		}
	}
	else
	{
		if (x <= xOld + bound - 30 && x >= xOld + bound - 31)
		{
			srand(time(0));
			r0 = rand() % 2;
			//if (r0 > 1)
			//	r0 = 1;
			turn *= (1 - 2 * r0);
		}
		if (x <= xOld - bound)
		{
			turn *= -1;
		}
	}
	vecX = turn * 1.5;
	x += vecX;
	
}

void SpearGuard::UpdateSprite()
{
	temp += 0.1;
	index = (int) temp;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		temp = startIndex;
	}
}



int SpearGuard::GetIndex()
{
	return index;
}

int SpearGuard::GetDirect()
{
	return turn;
}


SpearGuard::~SpearGuard()
{
}
