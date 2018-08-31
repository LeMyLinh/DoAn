#pragma once
#include "Enemy.h"
#include "EnemyRender.h"

class Panther :
	public Enemy
{
public:
	bool isSleeping;
	bool hasJump;
	bool isFight;
	float fid;
	float virtualVecX;
	bool IsFight;
	float delayMove;
	float localTime;
	Panther();
	Panther(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void Update(Box RectCamera, Box simon, int Deltatime);
	void UpdateSprite();
	void Draw();
	void CollisionWithObj(Object* obj);
	void UpdateMove(Box RectCamera, Box simon, int deltatime);
	bool CheckCollision(Box simon);
	Box GetBoundBox();

	~Panther();

};

