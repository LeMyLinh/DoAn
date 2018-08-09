#pragma once
#include "Enemy.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 

using namespace std;

class Pleaman: public Enemy
{
	float fid;
	bool IsJump;
	bool IsFight;
	int xold;
	int yold;
	int localTime;
	int delayMove;
	bool allowFalling;
	int turnOld;
	bool IsFalling;
	int HightJump;
	int timejump;
public:
	Pleaman();
	Pleaman(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	void CollisionWithObj(Object* obj);
	void UpdateMove(Box RectCamera, Box simon, int deltatime);
	Box GetBoundBox();
	~Pleaman();
};

