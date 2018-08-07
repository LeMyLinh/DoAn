#include "Ghost.h"
#include "EnemyRender.h"



Ghost::Ghost()
{
}

Ghost::Ghost(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	startIndex = 0;
	index = 0;
	endIndex = 1;
	//Infomation
	HP = 3;
	Damege = 2;
	Point = 300;
	temp = index;
	IsFight = false;
}
void Ghost::Update(Box RectCamera, Box simon, int Deltatime)
{
	Enemy::Update(RectCamera, simon, Deltatime);
	if (delay < 20)
	{
		delay++;
		return;
	}
	if (!IsFight)
	{		
		if (Collision::AABBCheck(this->GetBox(), simon))
		{
			IsFight = true;
			srand(time(0));
			int r0 = rand() % 2;
			turn *= (1 - 2 * r0);
			IsFight = true;
			if (turn == 1)
				x = RectCamera.x - 30;
			else
				x = RectCamera.x + RectCamera.w;
		}
	}
	else
	{
		UpdateSprite();
		
		//update position
		if (y < simon.y + simon.h - 40)
		{
			vecY = 0.8;
		}
		else if (y > simon.y + simon.h - 30)
		{
			vecY = -0.8;
		}
		else
			vecY = 0;

		if (turn == 1)
		{
			if (x > simon.x + simon.w)
				turn = -1;
		}
		else
			if (x + Width < simon.x)
				turn = 1;

		vecX = 2 * turn;
		x += vecX;
		y += vecY;
	}
}

void Ghost::UpdateSprite()
{
	temp += 0.4;
	index = (int)temp;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		temp = startIndex;
	}
}

void Ghost::Draw()
{
	if (IsFight)
		EnemyRender::GetStaticObj()->DrawGhost(x, y, index, turn);
}


Ghost::~Ghost()
{
}
