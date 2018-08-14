#ifndef _BLACKBOARD_H_
#define _BLACKBOARD_H_

#include "CText.h"
#include "Global.h"
#include "GSprite.h"
#include "Constant.h"
#include <string>

using namespace std;

class BlackBoard
{
public:
	long TimeValue, HeartValue;
	BlackBoard();
	~BlackBoard();
	void RenderFrame(int t, int x, int y, int simonHP);
	void PickUpItem(int itemID);
private:
	CText * LabelScore, *LabelPlayer, *LabelEnemy, *LabelTime, *LabelStage;
	CText *LabelHeart, *PValue;
	GTexture* blackboard, *T_Heal;
	GSprite* S_Heal;
	int Localtime;
	void LoadResources();
	void DrawPlayerValue(float x, float y, int simonHP);
	void DrawEnemyValue(float x, float y, int BossHP);
	void UpdateTime(int t);
	string ToString(long n);
	void Convert(char* main, char* text, long val);
	int x;
	int y;
};
#endif