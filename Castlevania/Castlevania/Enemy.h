#pragma once
#include "Object.h"
#include "Collision.h"
#include "Effect.h"
#include "Global.h"

class Enemy:public Object
{
protected:
	int HP;	
	int Point;
	//
	int startIndex;
	int endIndex;	
public:
	bool IsDie;
	int delay;
	int Damege;
	Enemy();
	Enemy(int _id, int _type, int _x, int _y, int _Width, int _Height);
	virtual void Update(Box RectCamera,Box simon, int Deltatime);
	virtual int GetIndex() { return index; }
	virtual int GetDirect() { return turn; }
	virtual void checkFight(Box vk ,int lv);
	virtual void Beaten(int lv);
	virtual void Draw() {};
	virtual bool CheckCollision(Box simon);
	virtual void CollisionWithObj(Object* obj) {}
	int GetHP();
	~Enemy();
};

