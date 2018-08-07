#pragma once
#include "Enemy.h"
#include "EnemyRender.h"
#include "Global.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>
#include <vector>
using namespace std;

class BosslV3 : public Enemy
{
	vector<Object> Thick;
	static float mau;
	int numBone;
	float fid;
	int localTime;
	int localTime1;
	int delayMove;
	int yold;
	int xold;
	int bound;
	int step;
	int wait;
	int direct;
	Object spritBall;
	//
	bool IsThrow;
	bool IsSleep;
	int delayFight;
public:
	BosslV3();
	BosslV3(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	void UpdateMove(Box RectCamera, Box simon, int deltatime);
	void Updatethick(Box camera);
	void checkFight(Box vk, int lv);
	bool CheckCollision(Box simon);
	void CollisionWithObj(Object* obj);
	~BosslV3();
};

