#include "Raven.h"



Raven::Raven()
{
}

Raven::Raven(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	//Infomation
	HP = 1;
	Damege = 3;
	Point = 200;
	IsFight = false;
	localTime = 0;
	maxTime = 0;
	startIndex = 1;
	index = 0;
	endIndex = 3;
	tid = startIndex;
	delayMove = 50;
	IsSkill = false;
	bound = 100;
}

void Raven::Update(Box RectCamera, Box simon, int Deltatime)
{
	Enemy::Update(RectCamera, simon, Deltatime);
	if (abs(x - simon.x) < 185 && abs(y - simon.y) < 280)
		IsFight = true;
	if (IsFight)
	{
		UpdateSprite();

		//delay move
		
		if (delayMove != 0)
			localTime += Deltatime;

		if (localTime >= delayMove || delayMove == 0)
		{
			//move
			localTime = 0;
			delayMove = 0;
			//update position
			//vecX += 0.08*turn;
			x += vecX;
			y += vecY;
			if (abs(x - xold) >= bound)
			{
				vecX = 0;
				delayMove = 900;
			}
		}
		else
		{
			//stop
			if (x < simon.x)
				turn = 1;
			else
				turn = -1;
			//
			if (y < simon.y + simon.w / 2)
				vecY = 3;
			else
				vecY = -3;

			srand(time(0));
			int r0 = rand() % 2 + 1;
			bound = 130 + (r0 - 1) * 50;
			vecX = 5 * turn;
			xold = x;
		}
	}
}

void Raven::UpdateSprite()
{
	tid += 0.4;
	index = (int)tid;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		tid = startIndex;
	}
}

void Raven::Draw()
{
	EnemyRender::GetStaticObj()->DrawRaven(x, y, index, turn);
}



Raven::~Raven()
{
}
