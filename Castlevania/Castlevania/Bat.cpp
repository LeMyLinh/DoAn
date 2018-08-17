#include "Bat.h"

Bat::Bat()
{
}

Bat::Bat(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	oldLocationX = x;
	oldLocationY = y;
	timeDelay = 0;
	step = 1;
	check = true;
	startIndex = 1;
	index = 0;
	endIndex = 2;
	vecY = 0;
	turn = 1;
	//Infomation
	HP = 1;
	Damege = 2;
	Point = 200;
	temp = index;
	IsFight = false;

}

void Bat::Update(Box RectCamera, Box simon, int Deltatime)
{

	if (delay < 50)
	{
		delay++;
		return;
	}
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
		/*if (y < simon.y + simon.h - 50)
		{
			vecY = 2;
		}
		else if (y > simon.y + simon.h - 25)
		{
			vecY = -2;
		}*/
		
		switch (step)
		{
		case 1:
			if (abs(x - oldLocationX) < 300)
			{

				if (direction == 1)
				{
					vecX = 2;
					vecY = 1;
				}
				else
				{
					vecX = -2;
					vecY = -1;
				}
			}
			else
			{
				vecX = 0;
				timeDelay++;
				vecY = 0.2;
				if (timeDelay > 50)
				{
					timeDelay = 0;

				}
				else
				{

					return;
				}
				step++;
			}
			break;
		case 2:
			if (x > oldLocationX && (x > oldLocationX-300))
			{
				direction = -1; 
				vecX = 5 * direction;
				turn = direction;
			}
			else if (x < oldLocationX && (oldLocationX+200 < x) < 300)
			{
				direction = 1;
				vecX = 5 * direction;
				turn = direction;
			}
			else//éo hiểu cái else này :)) viet all
			{
				vecX = 0;
				timeDelay++;
				if (timeDelay > 50)
				{
					timeDelay = 0;

				}
				else
				{

					return;
				}
				step++;
			}
			break;
		case 3:
			break;
		case 4:
			break;
		default:
			break;
		}

		////update position
		

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
	r.x = x - 100;
	r.w = 200;
	r.h = 100;
	return r;
}


Bat::~Bat()
{
}
