#include "EnemyRender.h"

EnemyRender* EnemyRender::pStaticObj = 0;

EnemyRender::EnemyRender()
{
}

void EnemyRender::Init()
{
	GTexture* texture1 = new GTexture();
	texture1->loadTextTureFromFile(L"Resources/enemy/5.png", D3DCOLOR_XRGB(255, 0, 255));
	SpearGuard = new GSprite(texture1, 4, 1, 0);
	//Bat
	GTexture* texture2 = new GTexture();
	texture2->loadTextTureFromFile(L"Resources/enemy/0.png", D3DCOLOR_XRGB(255, 0, 255));
	Bat = new GSprite(texture2, 4, 1, 0);
	//medusa
	GTexture* texture3 = new GTexture();
	texture3->loadTextTureFromFile(L"Resources/enemy/6.png", D3DCOLOR_XRGB(255, 0, 255));
	MedusaHead = new GSprite(texture3, 2, 1, 0);
	//ghost
	GTexture* texture4 = new GTexture();
	texture4->loadTextTureFromFile(L"Resources/enemy/9.png", D3DCOLOR_XRGB(255, 0, 255));
	Ghost = new GSprite(texture4, 2, 1, 0);
	//BonePillar;
	GTexture* texture5 = new GTexture();
	texture5->loadTextTureFromFile(L"Resources/enemy/8.png", D3DCOLOR_XRGB(255, 0, 255));
	BonePillar = new GSprite(texture5, 1, 1, 0);
	//moveplatform
	MovePlatform = new GTexture();
	MovePlatform->loadTextTureFromFile(L"Resources/ground/9.png", D3DCOLOR_XRGB(255, 0, 255));
	//trap
	GTexture* tt = new GTexture();
	tt->loadTextTureFromFile(L"Resources/ground/7_3.png", D3DCOLOR_XRGB(255, 0, 255));
	trap = new GSprite(tt, 2, 1, 0);
	//fireball
	fireBall = new GTexture();
	fireBall->loadTextTureFromFile(L"Resources/fireball.png", D3DCOLOR_XRGB(255, 0, 255));
	//bosslv2
	GTexture* ttbosslv2 = new GTexture();
	ttbosslv2->loadTextTureFromFile(L"Resources/boss/1.png", D3DCOLOR_XRGB(255, 0, 255));
	BossLv2 = new GSprite(ttbosslv2, 5, 1, 0);
	//snake
	GTexture* ttsnake = new GTexture();
	ttsnake->loadTextTureFromFile(L"Resources/boss/2.png", D3DCOLOR_XRGB(255, 0, 255));
	Snake = new GSprite(ttsnake, 2, 1, 1000 / 30);
	//pleaman
	GTexture* ttpleaman = new GTexture();
	ttpleaman->loadTextTureFromFile(L"Resources/enemy/10.png", D3DCOLOR_XRGB(255, 0, 255));
	Pleaman = new GSprite(ttpleaman, 2, 1, 0);
	//raven
	GTexture* ttraven = new GTexture();
	ttraven->loadTextTureFromFile(L"Resources/enemy/11.png", D3DCOLOR_XRGB(255, 0, 255));
	Raven = new GSprite(ttraven, 4, 1, 0);
	//Skeleton
	GTexture* ttSkeleton = new GTexture();
	ttSkeleton->loadTextTureFromFile(L"Resources/enemy/7.png", D3DCOLOR_XRGB(255, 0, 255));
	Skeleton = new GSprite(ttSkeleton, 4, 1, 0);
	//bone
	GTexture* ttBone = new GTexture();
	ttBone->loadTextTureFromFile(L"Resources/enemy/7_1.png", D3DCOLOR_XRGB(255, 0, 255));
	Bone = new GSprite(ttBone, 2, 1, 0);
	//boss lv3
	GTexture* ttblv3 = new GTexture();
	ttblv3->loadTextTureFromFile(L"Resources/boss/3.png", D3DCOLOR_XRGB(255, 0, 255));
	Bosslv3 = new GSprite(ttblv3, 6, 1, 0);
	//thick
	GTexture* tthick = new GTexture();
	tthick->loadTextTureFromFile(L"Resources/boss/3_1.png", D3DCOLOR_XRGB(255, 0, 255));
	Thick = new GSprite(tthick, 2, 1, 0);
}

EnemyRender * EnemyRender::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new EnemyRender();
	return pStaticObj;
}

void EnemyRender::DrawSpearGuard(int x, int y, int index, int turn)
{
	SpearGuard->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	SpearGuard->Draw(x + SpearGuard->_FrameWidth / 2, y + SpearGuard->_FrameHeight / 2, index);
}

void EnemyRender::DrawBat(int x, int y, int index, int turn)
{
	Bat->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Bat->Draw(x + Bat->_FrameWidth / 2, y + Bat->_FrameHeight / 2, index);
}

void EnemyRender::DrawMedusaHead(int x, int y, int index, int turn)
{
	MedusaHead->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	MedusaHead->Draw(x + MedusaHead->_FrameWidth / 2, y + MedusaHead->_FrameHeight / 2, index);
}

void EnemyRender::DrawGhost(int x, int y, int index, int turn)
{
	Ghost->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Ghost->Draw(x + Ghost->_FrameWidth / 2, y + Ghost->_FrameHeight / 2, index);
}


void EnemyRender::DrawMovePlatform(int x, int y)
{
	MovePlatform->RenderTexture(x + MovePlatform->Width / 2, y + MovePlatform->Height / 2);
}

void EnemyRender::DrawTrap(int x, int y, int index)
{
	trap->Draw(x + trap->_FrameWidth / 2, y + trap->_FrameHeight / 2, index);
}

void EnemyRender::DrawBonePillar(int x, int y, int turn)
{
	//BonePillar->SetColor(0xBBBBBB);
	BonePillar->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	BonePillar->Draw(x + BonePillar->_FrameWidth / 2, y + BonePillar->_FrameHeight / 2);
}

void EnemyRender::DrawFireBall(int x, int y, int turn)
{
	fireBall->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	fireBall->RenderTexture(x + fireBall->Width / 2, y + fireBall->Height / 2);
}

void EnemyRender::DrawBossLv2(int x, int y, int index)
{
	BossLv2->Draw(x + BossLv2->_FrameWidth / 2, y + BossLv2->_FrameHeight / 2, index);
}

void EnemyRender::DrawSnake(int x, int y, int index, int turn)
{
	Snake->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Snake->Draw(x + Snake->_FrameWidth / 2, y + Snake->_FrameHeight / 2);
}

void EnemyRender::DrawPleaman(int x, int y, int index, int turn)
{
	Pleaman->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Pleaman->Draw(x + Pleaman->_FrameWidth / 2, y + Pleaman->_FrameHeight / 2, index);
}

void EnemyRender::DrawRaven(int x, int y, int index, int turn)
{
	Raven->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Raven->Draw(x + Raven->_FrameWidth / 2, y + Raven->_FrameHeight / 2, index);
}

void EnemyRender::DrawSkeleton(int x, int y, int index, int turn)
{
	Skeleton->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Skeleton->Draw(x + Skeleton->_FrameWidth / 2, y + Skeleton->_FrameHeight / 2, index);
}

void EnemyRender::DrawBone(int x, int y, int index)
{
	Bone->Draw(x + Bone->_FrameWidth / 2, y + Bone->_FrameHeight / 2, index);
}

void EnemyRender::DrawBosslv3(int x, int y, int index, int turn)
{
	Bosslv3->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Bosslv3->Draw(x + Bosslv3->_FrameWidth / 2, y + Bosslv3->_FrameHeight / 2, index);
}

void EnemyRender::DrawThick(int x, int y, int index)
{
	Thick->Draw(x + Thick->_FrameWidth / 2, y + Thick->_FrameHeight / 2, index);
}


EnemyRender::~EnemyRender()
{
}
