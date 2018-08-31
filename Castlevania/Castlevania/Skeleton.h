#pragma once
#include "Enemy.h"
#include "EnemyRender.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>
#include <vector>
using namespace std;

class Skeleton : public Enemy
{
private:
	vector<Object> Bone;
	int numBone;
	int count;
	float fid;
	int localTime;
	int delayMove;
	int yold;
	int xold;
	int bound;
	int step;
	int direct;
	int wait;

	bool IsThrow;
	bool IsJump;
	bool IsFalling;
	bool allowFalling;
public:
	Skeleton();
	Skeleton(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	void CollisionWithObj(Object* obj);
	void UpdateMove(Box RectCamera, Box simon, int deltatime);
	void UpdateBone(Box camera);
	void checkFight(Box vk, int lv);
	bool CheckCollision(Box simon);
	~Skeleton();
};

