#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "Box.h"


enum Type
{
	//ground
	GroundBigLightHeart = 601, //k
	GroundBigLightRod = 602, //k
	GroundBigLightDagger = 603, //k
	GroundBigLight = 604, //k
	GroundSmallLightAxe = 605, //k
	GroundSmallLightBoomerang = 606,
	GroundSmallLightCross = 607,
	GroundSmallLightDoubleShot = 609, //k
	GroundSmallLightFireBomb = 608, //k
	GroundSmallLightRandom = 610,
	GroundSmallLightHeart = 620, //tim to
	GroundSmallLightSmallHeart = 600, 
	GroundSmallLightRod = 621, //k
	GroundSmallLightKnife = 622,
	GroundSmallLightBag1000 = 623,
	GroundSmallLightBag700 = 624,
	GroundSmallLightBag400 = 625,
	GroundTrident = 611, //cái T ngược
	GroundStair = 612, //k
	GroundUnknow = 613, //k
	ground = 614, //k
	GroundMovingPlatform = 615, //cái nền đi chuyển
	Gate = 659,
	Ground2 = 616,
	GroundStair2 = 617,
	GroundStiar3 = 618, //đầu cầu thang
	//hidden item
	ItemRoast = 626, //
	ItemDoubleShot = 627,
	ItemTripbleShot = 628, //k
	ItemHidden = 629, //chỗ gạch vỡ đc
	ItemCrown = 630,

	//boss
	BossLv1 = 401,
	BossLv2 = 402,
	BossLv3 = 403,

	// Enemy
	EnemyZombie = 201,// ma cà rồng map1
	EnemyBlackLeopard = 202,// con báo map1
	EnemyVampireBat = 203,// dơi map1
	EnemyMedusa = 204,// con có rắn
	EnemyFishMan = 205,//người cá map1
	EnemyAxeMan = 206,// thằng cầm rìu
	EnemyDragonSkullCannon = 207,//2 đầu lâu map2
	EnemyBlackNight = 208,//thằng cầm thương
	EnemyWhiteSkeleton = 209,// bộ xương trắng                                 
	EnemyGhost = 210,//ma map2        
	EnemyRaven = 211,
	EnemyPleaman = 212,


					 // Other
	Down = 801,
	Dead = 802,
	Right = 803,
	Up = 804,

	//Level5 + 6
	GROUND = 1,
	STAIR = 2,
	DOOR = 3,

	//Items
	SMALLHEART = 4,
	LARGEHEART = 5,
	BAG400 = 6,
	BAG700 = 7,
	BAG1000 =8,
	DOUBLESHOT = 9,
	TRIPLESHOT = 10,
	AXE = 11,
	BOOMERANG = 12,
	FIREBOMB = 13,

	//Enemy
	WHITESKELETON = 14,
	REDSKELETON = 15,
	PLEAMAN = 16,
	AXEKNIGHT = 17,
	BONEBILLAR = 18,
	MEDUSAHEAD = 19,
	EAGLE = 20,
	VAMPIREBAT = 21,

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



