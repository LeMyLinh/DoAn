#include "BonePillar.h"
#include "EnemyRender.h"


BonePillar::BonePillar()
{
}

BonePillar::BonePillar(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	//Infomation
	HP = 8;
	Damege = 2;
	Point = 400;
	IsFight = false;
	localTime = 0;
	maxTime = 0;
	localTime = 0;
}

void BonePillar::Update(Box RectCamera, Box simon, int Deltatime)
{
	//default
	Enemy::Update(RectCamera, simon, Deltatime);
	if (delay < 20)
	{
		delay++;
		//return;
	}
	//	
	if (!IsFight)
	{
		localTime += Deltatime;
		if (localTime < maxTime)
			return;
		else
		{
			localTime = 0;
		}
		if (x < simon.x)
			turn = 1;
		else
			turn = -1;

		ball1.SetObj(0, 0, (turn == -1) ? x : x + Width, y + 17, 14, 12);
		t = ball1.GetX();
		ball2.SetX(x);
		IsFight = true;
			
	}
	else
	{
		
		if (((t > x + 172 &&turn==1) || (t < x - 140 && turn == -1))&& ball2.GetX() == x)
		{
			ball2.SetObj(0, 0, (turn == -1) ? x - 1 : x + Width, y + 17, 14, 12);
		}
		ball1.SetX(5 * turn + ball1.GetX());
		t += 5 * turn;

		if (ball2.GetX() != x)
		{
			ball2.SetX(5 * turn + ball2.GetX());
			if (!Collision::AABBCheck(ball2.GetBox(), RectCamera))
			{
				IsFight = false;
				ball2.SetX(x);
				if (maxTime == 0)
					maxTime = 1000;
				else
					maxTime = 0;
			}
		}
	}	
}

void BonePillar::Effect()
{
}

void BonePillar::checkFight(Box vk, int lv)
{
	Enemy::checkFight(vk, lv);
	if (IsFight)
	{
		if (Collision::AABBCheck(vk, ball1.GetBox()))
		{
			Object* obj = new Object();
			obj->SetObj(-1, -1, ball1.GetX(), ball1.GetY(), 14, 12);
			Effect::GetStaticObj()->Add(obj);
			ball1.SetX(-1);		
		}
		if (Collision::AABBCheck(vk, ball2.GetBox()) && ball2.GetX() != x)
		{
			Object* obj = new Object();
			obj->SetObj(-1, -1, ball2.GetX(), ball2.GetY(), 14, 12);
			Effect::GetStaticObj()->Add(obj);
			ball2.SetX(x);
			IsFight = false;
			maxTime = 2000;
		}
	}
}

bool BonePillar::CheckCollision(Box simon)
{
	vecX = turn;
	if (Enemy::CheckCollision(simon))
		return true;
	 else if (IsFight)
	{
		if (Collision::AABBCheck(simon, ball1.GetBox()))
			return true;
		else if (ball2.GetX() != x)
			return Collision::AABBCheck(simon, ball2.GetBox());
	}
	return false;
}

void BonePillar::Draw()
{
	if (IsFight)
	{ 
		EnemyRender::GetStaticObj()->DrawFireBall(ball1.GetX(), ball1.GetY(), turn);
		if (ball2.GetX() != x)
			EnemyRender::GetStaticObj()->DrawFireBall(ball2.GetX(), ball2.GetY(), turn);
	}
		
	EnemyRender::GetStaticObj()->DrawBonePillar(x, y,turn);
}


BonePillar::~BonePillar()
{
}
