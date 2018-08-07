#include "Trap.h"
#include "EnemyRender.h"



Trap::Trap()
{
}

Trap::Trap(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	index = 0;
	vecY = 0;
	//gioi han
	bound = 90;
	vecX = 0;
	//Infomation
	HP = 3;
	Damege = 16;
	Point = 0;
	srand(time(0));
	temp = y;
	y += rand() % 4 * 5;
	localTime = 0;
	turn = 1;
}

void Trap::Update(Box RectCamera, Box simon, int Deltatime)
{
	if (turn == 1)
	{
		vecY = 5;
		if (y > temp + bound)
			turn = -1;
	}
	else
	{
		vecY = -1.5;
		if (y < temp)
			turn = 1;
	}

	y += vecY;
}

void Trap::Draw()
{
	for (int i = y - 28; i >= temp - 20; i -= 8)
	{
		EnemyRender::GetStaticObj()->DrawTrap(x, i, 1);
	}
	EnemyRender::GetStaticObj()->DrawTrap(x, y, 0);
}


Trap::~Trap()
{
}
