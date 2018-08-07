#pragma once
#include "Enemy.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
using namespace std;

class SpearGuard:public Enemy
{
protected:
	int bound;
	int xOld;
	float temp;
public:
	SpearGuard();
	SpearGuard(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera,Box simon, int Deltatime);
	void UpdateSprite();
	int GetIndex();
	int GetDirect();
	~SpearGuard();
};

