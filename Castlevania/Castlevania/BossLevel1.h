#pragma once
#include "Enemy.h"
#include"EnemyRender.h"

class BossLevel1 : public Enemy
{
	bool check;
	float temp;
	int direction;
	bool IsFight;
	int step;
	float time;
	float timeDelay;
	float oldLocationX;
	float oldLocationY;
public:
	BossLevel1();
	BossLevel1(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	Box GetBoundBox();
	~BossLevel1();
};

