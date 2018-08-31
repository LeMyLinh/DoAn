#pragma once
#include "GTexture.h"
#include "GSprite.h"

class EnemyRender
{
	static EnemyRender* pStaticObj;
	//sprite
	GSprite* Bat;
	GSprite* MedusaHead;
	GSprite* BonePillar;
	GTexture* fireBall;
	GSprite* Pleaman;
	GSprite* Skeleton;
	GSprite* Bone;
	GSprite* axeKnight;
	GSprite* redSkeleton;
	GSprite* panther;
	GSprite* perman;
	GSprite* zombie;
	GSprite* bossLv1;
	GSprite* bossLv5;
	GSprite* bossWeapon;
public:
	EnemyRender();
	void Init();
	static EnemyRender* GetStaticObj();
	void DrawBat(int x, int y, int index, int turn);
	void DrawMedusaHead(int x, int y, int index, int turn);
	void DrawBonePillar(int x, int y, int turn);
	void DrawFireBall(int x, int y, int turn);
	void DrawPleaman(int x, int y, int index, int turn);
	void DrawSkeleton(int x, int y, int index, int turn);
	void DrawBone(int x, int y, int index);
	void DrawAxeKnight(int x, int y, int index, int turn);
	void DrawRedSkeleton(int x, int y, int index, int turn);
	void DrawPanther(int x, int y, int index, int turn);
	void DrawPerman(int x, int y, int index, int turn);
	void DrawZombie(int x, int y, int index, int turn);
	void DrawBossLv1(int x, int y, int index, int turn);
	void DrawBossLv5(int x, int y, int index, int turn);
	void DrawBossWeapon(int x, int y, int index, int turn);
	~EnemyRender();
};

