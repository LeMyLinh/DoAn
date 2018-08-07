#pragma once
#include "Enemy.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>
using namespace std;

class Ghost: public Enemy
{
	float temp;
	bool IsFight;
public:
	Ghost();
	Ghost(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	~Ghost();
};

