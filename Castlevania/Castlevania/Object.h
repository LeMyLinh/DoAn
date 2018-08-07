#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "Box.h"


enum Type
{
	//ground
	GroundBigLightHeart = 601,
	GroundBigLightRod = 602,
	GroundBigLightDagger = 603,
	GroundBigLight = 604,
	GroundSmallLightAxe = 605,
	GroundSmallLightBoomerang = 606,
	GroundSmallLightCross = 607,
	GroundSmallLightDoubleShot = 609,
	GroundSmallLightFireBomb = 608,
	GroundSmallLightRandom = 610,
	GroundSmallLightHeart = 620,
	GroundSmallLightSmallHeart = 600,
	GroundSmallLightRod = 621,
	GroundSmallLightKnife = 622,
	GroundSmallLightBag1000 = 623,
	GroundSmallLightBag700 = 624,
	GroundSmallLightBag400 = 625,
	GroundTrident = 611,
	GroundStair = 612,
	GroundUnknow = 613,
	ground = 614,
	GroundMovingPlatform = 615,
	Gate = 659,
	Ground2 = 616,
	GroundStair2 = 617,
	GroundStiar3 = 618,
	//hidden item
	ItemRoast = 626,
	ItemDoubleShot = 627,
	ItemTripbleShot = 628,
	ItemHidden = 629,
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



