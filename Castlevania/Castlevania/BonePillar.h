#pragma once
#include "Enemy.h"

class BonePillar: public Enemy
{
	bool IsFight;
	int localTime;
	Object ball1;
	Object ball2;
	int maxTime;
	float t;
public:
	BonePillar();
	BonePillar(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void Effect();
	void checkFight(Box vk, int lv);
	bool CheckCollision(Box simon);
	void Draw();
	~BonePillar();
};

