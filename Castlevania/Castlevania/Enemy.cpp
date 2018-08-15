#include "Enemy.h"

Enemy::Enemy()
{
	IsDie = false;
	Damege = 0;
	Point = 0;
	delay = 20;
}

Enemy::Enemy(int _id, int _type, int _x, int _y, int _Width, int _Height) :Object(_id, _type, _x, _y, _Width, _Height)
{
	IsDie = false;
	Damege = 0;
	Point = 0;
	HP = 1;
	delay = 20;
}


void Enemy::Update(Box RectCamera, Box simon, int Deltatime)
{
	if (HP <= 0)
	{
		this->IsDie = true;
	}
}



void Enemy::checkFight(Box vk, int lv)
{
	if (IsDie)
		return;
	if (delay < 20)
		return;
	if (Collision::AABBCheck(vk, this->GetBox()))
	{
		Beaten(lv);
	}
}

void Enemy::Beaten(int lv)
{
	if (delay < 20)
		return;
	if (IsDie)
		return;
	delay = 0;
	HP -= lv;
	Object* obj = new Object();
	obj->SetObj(id, Type, x, y, Width, Heigt);
	Effect::GetStaticObj()->Add(obj);
	if (HP <= 0)
		G_ScoreValue += this->Point;
}

bool Enemy::CheckCollision(Box simon)
{
	return Collision::AABBCheck(simon, this->GetBox());
}

int Enemy::GetHP()
{
	return HP;
}

Enemy::~Enemy()
{
}
