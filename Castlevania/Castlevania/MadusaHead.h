#pragma once
#include "Enemy.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>

using namespace std;

class MadusaHead:public Enemy
{
private:
	float temp;
	bool IsFight;
	int delay;
	int localTime;
	int angle;
public:
	MadusaHead();
	MadusaHead(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	Box GetBoundBox(Box RectCamera);
	~MadusaHead();
};


