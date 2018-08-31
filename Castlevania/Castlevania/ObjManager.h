#ifndef _OBJMANAGER_H_
#define _OBJMANAGER_H_

#include "BaseObject.h"
#include <vector>
#include <d3d9.h>
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include "Tile.h"
#include "Object.h"
#include "Font.h"
#include <stdio.h>
#include "SmallCandle.h"
#include "BigCandle.h"
#include "BlockGate.h"
#include "Stair.h"
#include "TopStair.h"
#include <d3d9.h>
#include "Collision.h"
#include "EnemyRender.h"
#include "Enemy.h"
#include "Item.h"
#include "Gate.h"
#include "Weapon.h"
#include "Bat.h"
#include "MadusaHead.h"
#include "BonePillar.h"
#include "Pleaman.h"
#include "Skeleton.h"
#include "RedSkeleton.h"
#include "AxeKnight.h"
#include "Zombie.h"
#include "Panther.h"
#include "BossLevel1.h"

using namespace std;


class ObjManager
{
private:
	vector<int*> InfoObj;
	vector<int*> InfoObjTemp;
	vector<Object*> listObj;
	vector<Enemy*> listEnemy;
	RECT rect;
	ifstream f;
public:
	bool Isclear;
	int Frozen;
	ObjManager() 
	{
		Isclear = false;
		Frozen = 120;
	}
	
	bool IsNumber(char c)
	{
		if (c >= '0' && c <= '9')
			return true;
		return false;
	}
	
	void LoadFileInfo(char* fileGameObj)
	{
		
		f.open(fileGameObj, ios::in);
		string line;
		string strTemp = "";
		int i = 0;
		int *lTemp;

		while (!f.eof())
		{
			i = 0;
			lTemp = new int[7];
			strTemp = "";
			getline(f, line);
			if (line == "")
				break;
			for (int n = 0; n < line.length(); n++)
			{
				if (line[n] != '\t' && IsNumber(line[n]))
					strTemp += line[n];
				else
				{
					if (IsNumber(strTemp[0]))
					{
						int gt = atoi(strTemp.c_str());
						lTemp[i] = gt;
						strTemp = "";
						i++;
					}
				}
				if (n == line.length() - 1)
					lTemp[i] = atoi(strTemp.c_str());
			}
			lTemp[2] *= 2;
			lTemp[3] *= 2;
			lTemp[4] *= 2;
			lTemp[5] *= 2;
			lTemp[6] = 0;
			//add info object	
			InfoObj.push_back(lTemp);
		}
	}
	
	void Init(char* fileGameObj)
	{
		LoadFileInfo(fileGameObj);

		int* t;
		for (int i = 0; i < InfoObj.size(); i++)
		{
			t = new int[7];
			for (int j = 0; j < 7; j++)
			{
				t[j] = InfoObj[i][j];
			}
			InfoObjTemp.push_back(t);
		}	

	}
	
	void AddListAnemy(vector<int> tempEnemy, int* t)
	{
		for (int i = 0; i < tempEnemy.size(); i++)
		{
			Type _type;
			t = InfoObj[tempEnemy[i]];
			_type = (Type)t[1];
			Enemy* obj;
			switch (_type)
			{
			case BAT:
				obj = new Bat(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case MEDUSAHEAD:
				obj = new MadusaHead(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case BONEBILLAR:
				obj = new BonePillar(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case WHITESKELETON:
				obj = new Skeleton(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case PLEAMAN:
				obj = new Pleaman(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case AXEKNIGHT:
				obj = new AxeKnight(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case ZOMBIE:
				obj = new Zombie(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case REDSKELETON:
				obj = new RedSkeleton(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case PANTHER:
				obj=new Panther(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case PERMAN:
				break;
			case BOSSLEVEL1:
				obj = new BossLevel1(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			default:
				break;
			}			

			listEnemy.push_back(obj);
		}
	}
	
	void AddListObj()
	{		
		//Lưu thông tin object vs enemy
		vector<int> tempEnemy;
		int *t = new int[7];

		for (int i = 0; i < listObj.size(); i++)
		{
			delete listObj[i];
		}
		listObj.clear();
		for (int i = 0; i < InfoObj.size(); i++)
		{
			t = InfoObj[i];
			RECT check{ t[2],t[3], t[2] + t[4],t[3] + t[5] };
			if (Collision::CheckCollison(rect, check))
			{
				if ( (t[1] >= WHITESKELETON && t[1] <= PERMAN) || t[1] == BOSSLEVEL1)
				{
					//Load id enemy
					tempEnemy.push_back(InfoObj[i][0]);
				}
				else
				{
					Object* obj = new Object(t[0], t[1], t[2], t[3], t[4], t[5]);
					listObj.push_back(obj);
				}
			}
		}

		//load list enemy
		if (listEnemy.empty())
		{
			AddListAnemy(tempEnemy, t);
		}
		else
		{
			for (int i = 0; i < listEnemy.size(); i++)
			{
				for (int r = i + 1; r < listEnemy.size(); r++)
				{
					if (listEnemy[i]->GetID() == listEnemy[r]->GetID())
						listEnemy.erase(listEnemy.begin() + r);
				}
				bool check = false;
				for (int j = 0; j < tempEnemy.size(); j++)
				{
					if (listEnemy[i]->GetID() == tempEnemy[j])
					{
						tempEnemy.erase(tempEnemy.begin() + j);
						check = true;
						break;
					}
				}
				if (check == false && Collision::AABBCheck(listEnemy[i]->GetBox(), Box::ConvertRECT(rect)) == false)
				{
					delete listEnemy[i];
					listEnemy.erase(listEnemy.begin() + i);
				}
			}
			//add
			if (tempEnemy.empty())
				return;
			for (int i = 0; i < tempEnemy.size(); i++)
			{
				AddListAnemy(tempEnemy, t);
			}
		}
	}
	
	void UpDate(RECT rectCamera, vector<Object> &listItem,int DeltaTime,Box simon)
	{
		rect = rectCamera;

		AddListObj();

		if (Frozen < 120)
		{
			Isclear = true;
			Frozen++;
		}
		if (Isclear)
		{
			for (int i = 0; i < listEnemy.size(); i++)
			{
				if (listEnemy[i] == nullptr)
					continue;
				if (listEnemy[i]->IsDie == true)
					continue;
				listEnemy[i]->delay = 20;
				if (listEnemy[i]->GetHP() <= 0)
					listEnemy[i]->IsDie = true;
			}
			return;
		}
		for (int i = 0; i < listEnemy.size(); i++)
		{
			if (listEnemy[i] == nullptr)
				continue;
			if (listEnemy[i]->IsDie == true)
				continue;
			listEnemy[i]->Update(Box::ConvertRECT(rect),simon,DeltaTime);
		}
		
		//xu ly va cham
		HandlingCollisionWithGround(listItem,DeltaTime);
	}

	void Draw()
	{
		BigCandle::GetStaticObj()->Update();
		SmallCandle::GetStaticObj()->Update();
		//Draw gate
		CGate::GetStaticObj()->Draw();
		BlockGate::GetStaticObj()->Draw();

		if (Isclear)
		return;
		Type _type;
		//Draw object
		for (int i = 0; i < listObj.size(); i++)
		{			
			_type = (Type)listObj[i]->GetType();
			switch (_type)
			{
			case GROUND:
			case DOOR:
			case STAIR:
			case LEFTSTAIR:
				break;
			case KNIFE_BIGCANDLE:
			case MORNINGSTAR_BIGCANDLE:
			case LARGEHEART_BIGCANDLE:
				BigCandle::GetStaticObj()->Draw(listObj[i]->GetX(), listObj[i]->GetY());
				break;
			case BLOCKGATE:
				//BlockGate::GetStaticObj()->Draw();
				break;
			case DOUBLESHOT:
				if (InfoObj[listObj[i]->GetID()][6] == 1)
					Item::GetStaticObj()->DrawBreakWall(listObj[i]);
				break;
			case TRIPLESHOT:
				if (InfoObj[listObj[i]->GetID()][6] == 1)
					Item::GetStaticObj()->DrawBreakWall(listObj[i]);
				break;
			default:			
				SmallCandle::GetStaticObj()->Draw(listObj[i]->GetX(), listObj[i]->GetY());
				break;
			}
		}

		//Draw Enemy
		for (int i = 0; i < listEnemy.size(); i++)
		{
			_type = (Type)listEnemy[i]->GetType();			
			if (listEnemy[i]->IsDie)
				continue;
			switch (_type)
			{
			case REDSKELETON:
				listEnemy[i]->Draw();
				break;
			case WHITESKELETON:
				listEnemy[i]->Draw();
				break;
			case PLEAMAN:
				listEnemy[i]->Draw();
				break;
			case AXEKNIGHT:
				EnemyRender::GetStaticObj()->DrawAxeKnight(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case BAT:
				EnemyRender::GetStaticObj()->DrawBat(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case ZOMBIE:
				EnemyRender::GetStaticObj()->DrawZombie(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case PANTHER:
				EnemyRender::GetStaticObj()->DrawPanther(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case BONEBILLAR:
				EnemyRender::GetStaticObj()->DrawBonePillar(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex());
				break;
			case MEDUSAHEAD:
				EnemyRender::GetStaticObj()->DrawMedusaHead(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case PERMAN:
				break;
			case BOSSLEVEL1:
				EnemyRender::GetStaticObj()->DrawBossLv1(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
			default:
				break;
			}
		}
		
		char str[100];
		sprintf_s(str, " %d  ", listEnemy.size());
		RECT rect{ 0,0,300,100 };
		Font::GetFont()->Render(NULL, str, rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}

	vector<Object*> GetListObj()
	{
		return listObj;
	}

	vector<int*> GetListInfo()
	{
		return InfoObj;
	}

	void HandlingCollisionWithGround(vector<Object> &listItem,int DeltaTime)
	{
		for (int i = 0; i < listObj.size(); i++)
		{
			//xu ly va cham voi mat dat
			if (listObj[i]->GetType() == GROUND)
			{
				//item
				Item::GetStaticObj()->CollisionHandle(listObj[i]);
				Type _type;
				Box tempBox;
				Box tempBox2;
				int count;
				int count2;
				//Enemy
				for (int j = 0; j < listEnemy.size(); j++)
				{
					_type = (Type)listEnemy[j]->GetType();
					switch (_type)
					{
					case AXEKNIGHT:
						if (Collision::HitTheWall(listEnemy[j]->GetBox(), listObj[i]->GetBox()))
						{
							listEnemy[j]->SetVec(listEnemy[j]->GetBox().vx*(-1), listEnemy[j]->GetBox().vy);
							listEnemy[j]->turn *= -1;
						}
						tempBox = listEnemy[j]->GetBox();
						tempBox.x += tempBox.w +3;
						tempBox.w = 2;
						tempBox2 = listEnemy[j]->GetBox();
						tempBox2.x -=3;
						tempBox2.w = 2;
						count = 0;
						count2 = 0;
						for (int n = 0; n < listObj.size(); n++)
						{
							if (Collision::AABBCheck(tempBox, listObj[n]->GetBox()) == false && listEnemy[j]->turn==1)
							{
								count++;
							}
							if (Collision::AABBCheck(tempBox2, listObj[n]->GetBox()) == false && listEnemy[j]->turn == -1)
							{
								count2++;
							}
						}	
						if (count == listObj.size() || count2 == listObj.size())
						{
							listEnemy[j]->SetVec(listEnemy[j]->GetBox().vx*(-1), listEnemy[j]->GetBox().vy);
							listEnemy[j]->turn *= -1;
						}
						break;
					case WHITESKELETON:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case PLEAMAN:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case REDSKELETON:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case ZOMBIE:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case BAT:
						break;
					case BONEBILLAR:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case PANTHER:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case PERMAN:
						break;
					case MEDUSAHEAD:
						break;
					default:
						break;
					}
				}
				//Weapon
				Weapon::GetStaticObj()->Collison(listObj[i],DeltaTime);
			}
		}
	}

	vector<Enemy*> GetlistEnemy()
	{
		return listEnemy;
	}
	void Reset()
	{
		for (int i = 0; i < listEnemy.size(); i++)
		{
			delete listEnemy[i];
		}
		listEnemy.clear();
		InfoObj.clear();
		int* t;
		for (int i = 0; i < InfoObjTemp.size(); i++)
		{
			t = new int[7];
			for (int j = 0; j < 7; j++)
			{
				t[j] = InfoObjTemp[i][j];
			}
			InfoObj.push_back(t);
		}
	}
	void Delete()
	{
		for (int i = 0; i < listEnemy.size(); i++)
		{
			listEnemy[i]->IsDie = true;
			Effect::GetStaticObj()->Add(listEnemy[i]);
		}
	}
	~ObjManager() 
	{ 
		f.close();
	}
};
#endif // !_OBJMANAGER_H_




