#include "EnemyRender.h"

EnemyRender* EnemyRender::pStaticObj = 0;

EnemyRender::EnemyRender()
{
}

void EnemyRender::Init()
{
	//Bat
	GTexture* texture2 = new GTexture();
	texture2->loadTextTureFromFile(L"Resources/enemy/bat.png", D3DCOLOR_XRGB(255, 0, 255));
	Bat = new GSprite(texture2, 4, 1, 0);
	//medusa
	GTexture* texture3 = new GTexture();
	texture3->loadTextTureFromFile(L"Resources/enemy/head.png", D3DCOLOR_XRGB(255, 0, 255));
	MedusaHead = new GSprite(texture3, 2, 1, 0);
	//BonePillar;
	GTexture* texture5 = new GTexture();
	texture5->loadTextTureFromFile(L"Resources/enemy/boneBillar.png", D3DCOLOR_XRGB(255, 0, 255));
	BonePillar = new GSprite(texture5, 1, 1, 0);
	//fireball
	fireBall = new GTexture();
	fireBall->loadTextTureFromFile(L"Resources/fireball.png", D3DCOLOR_XRGB(255, 0, 255));
	//pleaman
	GTexture* ttpleaman = new GTexture();
	ttpleaman->loadTextTureFromFile(L"Resources/enemy/hunchback.png", D3DCOLOR_XRGB(255, 0, 255));
	Pleaman = new GSprite(ttpleaman, 2, 1, 0);
	//Skeleton
	GTexture* ttSkeleton = new GTexture();
	ttSkeleton->loadTextTureFromFile(L"Resources/enemy/skeleton.png", D3DCOLOR_XRGB(255, 0, 255));
	Skeleton = new GSprite(ttSkeleton, 4, 1, 0);
	//bone
	GTexture* ttBone = new GTexture();
	ttBone->loadTextTureFromFile(L"Resources/enemy/bone.png", D3DCOLOR_XRGB(255, 0, 255));
	Bone = new GSprite(ttBone, 2, 1, 0);
	//AxeKnight
	GTexture* ttAxeKnight = new GTexture();
	ttAxeKnight->loadTextTureFromFile(L"Resources/enemy/axeKnight.png", D3DCOLOR_XRGB(255, 0, 255));
	axeKnight = new GSprite(ttAxeKnight, 2, 1, 0);
	//RedSkeleton
	GTexture* ttRedSkeleton = new GTexture();
	ttRedSkeleton->loadTextTureFromFile(L"Resources/enemy/RedSkeleton.png", D3DCOLOR_XRGB(255, 0, 255));
	redSkeleton = new GSprite(ttRedSkeleton, 4, 1, 0);
	//Panther
	GTexture* ttPanther = new GTexture();
	ttPanther->loadTextTureFromFile(L"Resources/enemy/Panther.png", D3DCOLOR_XRGB(255, 0, 255));
	panther = new GSprite(ttPanther, 4, 1, 0);
	//Perman
	GTexture* ttPerman = new GTexture();
	ttPerman->loadTextTureFromFile(L"Resources/enemy/Perman.png", D3DCOLOR_XRGB(255, 0, 255));
	perman = new GSprite(ttPerman, 3, 1, 0);
	//Zombie
	GTexture* ttZombie = new GTexture();
	ttZombie->loadTextTureFromFile(L"Resources/enemy/Zombie.png", D3DCOLOR_XRGB(255, 0, 255));
	zombie = new GSprite(ttZombie, 2, 1, 0);
	//BossLv1
	GTexture* ttBoss1 = new GTexture();
	ttBoss1->loadTextTureFromFile(L"Resources/boss/BossLv1.png", D3DCOLOR_XRGB(255, 0, 255));
	bossLv1 = new GSprite(ttBoss1, 3, 1, 0);
	//BossLv5
	GTexture* ttBoss5 = new GTexture();
	ttBoss5->loadTextTureFromFile(L"Resources/boss/BossLevel5_1.png", D3DCOLOR_XRGB(255, 0, 255));
	bossLv5 = new GSprite(ttBoss5, 1, 1, 0);
	//boss weapon
	GTexture* ttbossWeapon = new GTexture();
	ttbossWeapon->loadTextTureFromFile(L"Resources/boss/bossWeapon.png", D3DCOLOR_XRGB(255, 0, 255));
	bossWeapon = new GSprite(ttbossWeapon, 4, 1, 0);
}

EnemyRender * EnemyRender::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new EnemyRender();
	return pStaticObj;
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


void EnemyRender::DrawPleaman(int x, int y, int index, int turn)
{
	Pleaman->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	Pleaman->Draw(x + Pleaman->_FrameWidth / 2, y + Pleaman->_FrameHeight / 2, index);
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

void EnemyRender::DrawAxeKnight(int x, int y, int index, int turn)
{
	axeKnight->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	axeKnight->Draw(x + axeKnight->_FrameWidth / 2, y + axeKnight->_FrameHeight / 2, index);
}
void EnemyRender::DrawRedSkeleton(int x, int y, int index, int turn)
{
	redSkeleton->SetFormat(D3DXVECTOR2(turn, 1), 0, 1);
	redSkeleton->Draw(x + redSkeleton->_FrameWidth / 2, y + redSkeleton->_FrameHeight / 2, index);

}
void EnemyRender::DrawPanther(int x, int y, int index, int turn)
{
	panther->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	panther->Draw(x + panther->_FrameWidth / 2, y + panther->_FrameHeight / 2, index);

}
void EnemyRender::DrawPerman(int x, int y, int index, int turn)
{
	perman->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	perman->Draw(x + perman->_FrameWidth / 2, y + perman->_FrameHeight / 2, index);

}
void EnemyRender::DrawZombie(int x, int y, int index, int turn)
{
	zombie->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
	zombie->Draw(x + zombie->_FrameWidth / 2, y + zombie->_FrameHeight / 2, index);

}
void EnemyRender::DrawBossLv1(int x, int y, int index, int turn)
{
	bossLv1->SetFormat(D3DXVECTOR2(turn, 1), 0, 1);
	bossLv1->Draw(x + bossLv1->_FrameWidth / 2, y + bossLv1->_FrameHeight / 2, index);

}
void EnemyRender::DrawBossLv5(int x, int y, int index, int turn)
{
	bossLv5->SetFormat(D3DXVECTOR2(turn, 1), 0, 1);
	bossLv5->Draw(x + bossLv5->_FrameWidth / 2, y + bossLv5->_FrameHeight / 2, index);

}
void EnemyRender::DrawBossWeapon(int x, int y, int index, int turn)
{
	bossWeapon->SetFormat(D3DXVECTOR2(turn, 1), 0, 1);
	bossWeapon->Draw(x + bossWeapon->_FrameWidth / 2, y + bossWeapon->_FrameHeight / 2, index);

}

EnemyRender::~EnemyRender()
{
}
