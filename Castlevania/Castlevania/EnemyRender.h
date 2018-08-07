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
	GSprite* Ghost;
	GSprite* BonePillar;
	GTexture* MovePlatform;
	GSprite* trap;
	GTexture* fireBall;
	GSprite* BossLv2;
	GSprite* Pleaman;
	GSprite* Raven;
	GSprite* Skeleton;
	GSprite* Bone;
	GSprite* Bosslv3;
	GSprite* Thick;
public:
	GSprite* Snake;
	EnemyRender();
	void Init();
	static EnemyRender* GetStaticObj();
	void DrawSpearGuard(int x, int y, int index, int turn);
	void DrawBat(int x, int y, int index, int turn);
	void DrawMedusaHead(int x, int y, int index, int turn);
	void DrawGhost(int x, int y, int index, int turn);
	void DrawMovePlatform(int x, int y);
	void DrawTrap(int x, int y, int index);
	void DrawBonePillar(int x, int y, int turn);
	void DrawFireBall(int x, int y, int turn);
	void DrawBossLv2(int x, int y, int index);
	void DrawSnake(int x, int y, int index, int turn);
	void DrawPleaman(int x, int y, int index, int turn);
	void DrawRaven(int x, int y, int index, int turn);
	void DrawSkeleton(int x, int y, int index, int turn);
	void DrawBone(int x, int y, int index);
	void DrawBosslv3(int x, int y, int index, int turn);
	void DrawThick(int x, int y, int index);
	~EnemyRender();
};

