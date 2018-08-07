#pragma once
#include <vector>
#include "Object.h"
#include "GTexture.h"
#include "GSprite.h"
using namespace std;


class Item
{
	static Item* pStaticObj;
	vector<Object> listItem;
	
public:
	Object* beakWall;
	GTexture* Heart;
	GTexture* bigHeart;	
	GSprite* Bag;
	GTexture* morningStar;
	GTexture* Roast; //dui ga
	GTexture* rosary; // clear anemy
	GSprite* crown; //vuong niem
	GTexture* treasureChest;//kho bao
	GTexture* Invincible; //bao ve
	GTexture* Hidden; //tang hinh
	GTexture* doubleShot;
	GTexture* tripleShot;
	GSprite* spriritBall;
	GTexture* lvUp;
	GTexture* knife;
	//weapon
	GTexture* Bomerang;
	GTexture* axe;
	GTexture* boom;
	GTexture* BreakWall;
	GTexture* iconDoubleShot;
	GTexture* iconTripbleShot;
	GTexture* StopWatch;
	//
	bool b;

	Item();
	void Init();
	void Update(int Delta);
	static Item* GetStaticObj();
	void Add(Object* o, int power);
	void Draw(int Delta);
	vector<Object> GetListItem();
	void RemoveAt(int i);
	void setXY(int i, int x, int y);
	void CollisionHandle(Object* o);
	void DrawBreakWall(Object* o);
	~Item();
};

