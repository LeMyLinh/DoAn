#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "Box.h"


enum Type
{
	Down = 801,
	Dead = 802,
	Right = 803,
	Up = 804,

	//Level5
	GROUND = 1,
	STAIR = 2,
	DOOR = 3,
	LEFTSTAIR = 24,
	TOPSTAIR = 25,
	STAIRUN = 26,
	BLOCKGATE = 27,
	//Items
	BIGCANDLE = 28,
	STOPWATCH = 29,
	KNIFE = 30,
	MORNINGSTAR = 31,
	HOLYWATER = 32,
	SMALLHEART = 4,
	LARGEHEART = 5,
	BAG400 = 6,
	BAG700 = 7,
	BAG1000 = 8,
	DOUBLESHOT = 9,
	TRIPLESHOT = 10,
	AXE = 11,
	CROSS = 12,
	FIREBOMB = 13,

	//Enemy
	WHITESKELETON = 14,
	REDSKELETON = 15,
	PLEAMAN = 16,
	AXEKNIGHT = 17,
	BONEBILLAR = 18,
	MEDUSAHEAD = 19,
	ZOMBIE = 20,
	BAT = 21,
	PANTHER = 22,
	PERMAN = 23,


};


class Object
{
protected:
	///position
	float x;
	float y;
	float vecX;
	float vecY;	
	int Type;
	int id;		
public:
	//index of sprite
	int Width;
	int Heigt;
	bool IsDie;
	int index;
	int turn;
	int temp;
	virtual int GetIndex();
	virtual int GetDirect();
	Object();
	Object(int _id, int _type, int _x, int _y, int _Width, int _Height);
	void SetObj(int _id, int _type, int _x, int _y, int _Width, int _Height);
	virtual void Update(Box RectCamera) {}
	void Update();
	int GetID();
	int GetX();
	int GetY();
	int GetType();
	void SetX(int v);
	void SetY(int v);
	void SetVec(float vc, float vy);
	void SetVx(float vx);
	void SetVy(float vy);
	void SetType(int type);
	virtual Box GetBox();
	~Object();
};
#endif // !_OBJECT_H_



