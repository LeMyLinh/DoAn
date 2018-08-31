#include "AxeKnight.h"

AxeKnight::AxeKnight()
{
}

AxeKnight::AxeKnight(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
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
	Damage = 2;
	Point = 400;
	temp = index;
}

void AxeKnight::Update(Box RectCamera, Box simon, int Deltatime)
{
	Enemy::Update(RectCamera, simon, Deltatime);
	if (delay < 20)
	{
		delay++;
		return;
	}
	int r0;
	UpdateSprite();
	if (vecX > 0)
	{
		if (x >= xOld - bound + 30 && x <= xOld - bound + 33)
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
	if (IsFight)
	{

		if (Collision::AABBCheck(Wpaxe.GetBox(), RectCamera) == false)
		{
			Object* obj = new Object();
			obj->SetObj(-1, -1, Wpaxe.GetX(), Wpaxe.GetY(), 14, 12);
			Effect::GetStaticObj()->Add(obj);



		}
		Wpaxe.SetX(Wpaxe.GetX() + Wpaxe.GetBox().vx);

		if (Wpaxe.temp == Wpaxe.turn)
		{
			center.y -= 3;
			if (center.y <= 3)
				Wpaxe.temp *= -1;
		}
		Wpaxe.SetVy(sin(center.y)*(130));

		Wpaxe.SetY(Wpaxe.GetY() + Wpaxe.GetBox().vy);

	}
}


void AxeKnight::UpdateSprite()
{
	temp += 0.1;
	index = (int)temp;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		temp = startIndex;
	}
}



int AxeKnight::GetIndex()
{
	return index;
}

int AxeKnight::GetDirect()
{
	return turn;
}

void AxeKnight::Draw()
{
	if (IsFight)
	{

		Axe->Draw(Wpaxe.GetX() + Wpaxe.GetBox().w / 2, Wpaxe.GetY() + Wpaxe.GetBox().h / 2, Wpaxe.index);
	}

	EnemyRender::GetStaticObj()->DrawAxeKnight(x, y, index, turn);
}


AxeKnight::~AxeKnight()
{
}
