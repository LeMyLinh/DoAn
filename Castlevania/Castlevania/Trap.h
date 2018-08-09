#pragma once
#include "Enemy.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 

using namespace std;

class Trap: public Enemy
{
protected:
	int bound;
	int localTime;
public:
	Trap();
	Trap(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void Draw();
	~Trap();
};

