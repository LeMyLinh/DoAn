#pragma once
#include "Enemy.h"

class MovePlatform:public Enemy
{
protected:
	int bound;
	int xOld;
public:
	MovePlatform();
	MovePlatform(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	~MovePlatform();
};
