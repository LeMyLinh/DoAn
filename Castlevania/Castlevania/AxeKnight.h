#pragma once

#include "Enemy.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include "Weapon.h"
#include "EnemyRender.h"
using namespace std;

class AxeKnight : public Enemy
{
protected:
	int bound;
	int xOld;
	float temp;
	Object Wpaxe;
	D3DXVECTOR2 center;
	GSprite* Axe;
	bool IsFight;
public:
	AxeKnight();
	AxeKnight(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	int GetIndex();
	int GetDirect();
	void Draw();
	~AxeKnight();
};
