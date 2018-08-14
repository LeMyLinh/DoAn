#pragma once
#include "GTexture.h"
#include "GSprite.h"

class EnemyRender
{
	static EnemyRender* pStaticObj;
	//sprite
	GSprite* SpearGuard;
	GSprite* Bat;
	GSprite* MedusaHead;
	GSprite* BonePillar;
	GTexture* fireBall;
	GSprite* Pleaman;
	GSprite* Skeleton;
	GSprite* Bone;
	GSprite* Thick;
public:
	EnemyRender();
	void Init();
	static EnemyRender* GetStaticObj();
	void DrawSpearGuard(int x, int y, int index, int turn);
	void DrawBat(int x, int y, int index, int turn);
	void DrawMedusaHead(int x, int y, int index, int turn);
	void DrawBonePillar(int x, int y, int turn);
	void DrawFireBall(int x, int y, int turn);
	void DrawPleaman(int x, int y, int index, int turn);
	void DrawSkeleton(int x, int y, int index, int turn);
	void DrawBone(int x, int y, int index);
	void DrawThick(int x, int y, int index);
	~EnemyRender();
};

