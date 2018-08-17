#include "BlackBoard.h"
#include "Object.h"
#include "Item.h"
#include "Weapon.h"
#include <string.h>

#pragma warning(disable:4996)
BlackBoard::BlackBoard()
{
	Localtime = 0;
	x = 0;
	y = 0;
	LoadResources();
}
void BlackBoard::LoadResources()
{
	LabelScore = new CText("SCORE-00000000", 26, 10, 5, D3DCOLOR_ARGB(255, 255, 255, 255));
	LabelPlayer = new CText("PLAYER", 26, 10, 35, D3DCOLOR_ARGB(255, 255, 255, 255));
	LabelEnemy = new CText("ENEMY", 26, 10, 65, D3DCOLOR_ARGB(255, 255, 255, 255));
	LabelTime = new CText("TIME-0300", 26, 250, 5, D3DCOLOR_ARGB(255, 255, 255, 255));
	LabelStage = new CText("STAGE 01", 26, 400, 5, D3DCOLOR_ARGB(255, 255, 255, 255));
	LabelHeart = new CText("05", 26, 441, 40, D3DCOLOR_ARGB(255, 255, 255, 255));
	PValue = new CText("03", 26, 441, 60, D3DCOLOR_ARGB(255, 255, 255, 255));

	TimeValue = 300;
	HeartValue = 5;

	blackboard = new GTexture();
	blackboard->loadTextTureFromFile(BLACKBOARD_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	T_Heal = new GTexture();
	T_Heal->loadTextTureFromFile(HEAL_IMAGE, D3DCOLOR_XRGB(255, 0, 255));
	S_Heal = new GSprite(T_Heal, 3, 1, 50);
}
BlackBoard::~BlackBoard()
{
}
void BlackBoard::RenderFrame(int t, int x, int y, int simonHP)
{
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	Convert(LabelHeart->Text, "", HeartValue);
	Convert(LabelScore->Text, "SCORE-", G_ScoreValue);
	Convert(LabelStage->Text, "STAGE-", G_Stage);
	blackboard->RenderTexture(x + blackboard->Width / 2, y - 90 + blackboard->Height / 2);

	switch (Weapon::GetStaticObj()->typeWP)
	{
	case 2:
		Item::GetStaticObj()->Bomerang->RenderTexture(x + blackboard->Width / 2 + 37, y - 90 + blackboard->Height / 2 + 10);
		break;
	case 3:
		Item::GetStaticObj()->axe->RenderTexture(x + blackboard->Width / 2 + 37, y - 90 + blackboard->Height / 2 + 10);
		break;
	case 4:
		Item::GetStaticObj()->boom->RenderTexture(x + blackboard->Width / 2 + 37, y - 90 + blackboard->Height / 2 + 10);
		break;
	default:
		break;
	}

	if (Weapon::GetStaticObj()->MultiShot == 2)
		Item::GetStaticObj()->iconDoubleShot->RenderTexture(x + blackboard->Width / 2 + 180, y - 90 + blackboard->Height / 2 + 10);
	if (Weapon::GetStaticObj()->MultiShot == 3)
		Item::GetStaticObj()->iconTripbleShot->RenderTexture(x + blackboard->Width / 2 + 180, y - 90 + blackboard->Height / 2 + 10);
	DrawPlayerValue(x + T_Heal->Width / 2 + 100, y - 90 + T_Heal->Height / 2 + 40, simonHP);
	DrawEnemyValue(x + T_Heal->Width / 2 + 100, y - 90 + T_Heal->Height / 2 + 70, G_bossHP);
	G_SpriteHandler->End();
	LabelScore->Draw();
	LabelPlayer->Draw();
	LabelEnemy->Draw();
	LabelTime->Draw();
	LabelStage->Draw();
	LabelHeart->Draw();
	//Time->Draw();
	PValue->Draw();
	UpdateTime(t);
	this->x = x + T_Heal->Width / 2 + 50;
	this->y = y + T_Heal->Height / 2 + 50;
	//

}
void BlackBoard::UpdateTime(int t)
{
	Localtime += t;
	if (Localtime > 400)
	{
		Localtime = 0;
		Convert(LabelTime->Text, "TIME-", TimeValue--);
	}
}
void BlackBoard::DrawPlayerValue(float x, float y, int simonHP)
{
	for (int i = 0; i < 16; i++)
	{
		if (i < simonHP)
		{
			S_Heal->Draw(x, y, 0);
		}
		else
		{
			S_Heal->Draw(x, y, 1);
		}
		x += 10;
	}
}
void BlackBoard::DrawEnemyValue(float x, float y, int BossHP)
{
	for (int i = 0; i < 16; i++)
	{
		if (i < BossHP)
		{
			S_Heal->Draw(x, y, 0);
		}
		else
		{
			S_Heal->Draw(x, y, 1);
		}
		x += 10;
	}
}
string BlackBoard::ToString(long n)
{
	string s;
	while (n > 0)
	{
		s = char('0' + n % 10) + s;
		n = n / 10;
	}
	return s;
}
void BlackBoard::Convert(char* main, char* text, long val)
{
	string s = ToString(val);
	int n = strlen(main) - strlen(text) - s.length();

	string result = text;
	for (int i = 0; i < n; i++) result += '0';
	result += s;
	std::strcpy(main, result.c_str());
}
void BlackBoard::PickUpItem(int itemID)
{
	Type _type;
	_type = (Type)itemID;
	switch (_type)
	{
	case AXE:
		break;
	case CROSS:
		break;
	case FIREBOMB:
		break;
	case LARGEHEART:
		HeartValue += 5;
		break;
	case SMALLHEART:
		HeartValue += 1;
		break;
	case BAG1000:
		G_ScoreValue += 1000;
		break;
	case BAG700:
		G_ScoreValue += 700;
		break;
	case BAG400:
		G_ScoreValue += 400;
		break;
	default:
		break;
	}
}