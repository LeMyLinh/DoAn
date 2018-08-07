#pragma once
#include "Enemy.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>
using namespace std;


class BossLV2:public Enemy
{
	bool IsFight;
	float tid;
	int localTime;
	Object snake;
	int maxTime;
	int delayMove;
	bool IsSkill;
	float t;
	int bound;
	bool move;
	float vt;
	float xold;
	float yold;
	int turnOld;
	Object spritBall;

public:
	BossLV2();
	BossLV2(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Effect();
	void checkFight(Box vk, int lv);
	bool CheckCollision(Box simon);
	void Draw();
	void Skill(Box simon);
	void CollisionWithObj(Object* obj);
	void UpdateMove(Box RectCamera, Box simon);
	~BossLV2();
};

