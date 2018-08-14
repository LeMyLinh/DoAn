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
	GTexture* Heart;
	GTexture* bigHeart;	
	GSprite* Bag;
	GTexture* morningStar;
	GTexture* rosary; // clear anemy
	GTexture* treasureChest;//kho bao
	GTexture* Invincible; //bao ve
	GTexture* Hidden; //tang hinh
	GTexture* doubleShot;
	GTexture* tripleShot;
	GSprite* spriritBall;
	//weapon
	GTexture* Bomerang;
	GTexture* axe;
	GTexture* boom;
	GTexture* iconDoubleShot;
	GTexture* iconTripbleShot;
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

