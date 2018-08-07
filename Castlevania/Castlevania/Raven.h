#pragma once
#include "Enemy.h"
#include "EnemyRender.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>
using namespace std;

class Raven: public Enemy
{
	bool IsFight;
	float tid;
	int localTime;
	int maxTime;
	int delayMove;
	bool IsSkill;
	float t;
	int bound;
	bool move;
	float vt;
	float xold;
public:
	Raven();
	Raven(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	~Raven();
};

