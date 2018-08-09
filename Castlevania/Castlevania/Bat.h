#pragma once
#include "Enemy.h"


class Bat: public Enemy
{
	float temp;
	int direction;
	bool IsFight;
public:
	Bat();
	Bat(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	Box GetBoundBox();
	~Bat();
};

