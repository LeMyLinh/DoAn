#pragma once

#include "Object.h"
#include "GTexture.h"
#include "GSprite.h"
#include "Collision.h"
#include "BlackBoard.h"
#include <vector>

using namespace std;

class Weapon
{
	static Weapon* pStaticObj;
	GSprite* Bomerang; //2
	GSprite* Axe; //3
	GSprite* Bom; //4
	bool IsFight;
	bool IsReady;
	int localTime;
	float time;
	//Weapon
	vector<Object> listWeapon;
	vector<D3DXVECTOR2> tami;
	
	
public:
	int typeWP;
	int damge;
	int MultiShot;

	Weapon();
	bool Ready();
	void Init();
	static Weapon* GetStaticObj();
	void CheckWeaponInItem(Object item);
	void Fight(int _x, int _y, int turn, BlackBoard* lackBoard);
	void Update(RECT camera, BlackBoard* lackBoard,Box Simon, int DeltaTime);
	void UpdateKnife(RECT camera);
	void UpdateBoomerang(RECT camera, Box Simon);
	void UpdateAxe(RECT camera, int DeltaTime);
	void UpdateBoom(RECT camera, int DeltaTime);
	void Collison(Object* obj, int DeltaTime);
	bool Check(Object* obj);
	void Draw();
	void UpdateIndex(int &index,int delta);
	void Reset();
	~Weapon();
};

