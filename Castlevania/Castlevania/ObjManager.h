#ifndef _OBJMANAGER_H_
#define _OBJMANAGER_H_

#include "QuadTree.h"
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
#include "BigCandel.h"
#include "SmallCandle.h"
#include "Stair.h"
#include "TopStair.h"
#include <d3d9.h>
#include "Collision.h"
#include "EnemyRender.h"
#include "SpearGuard.h"
#include "Enemy.h"
#include "Item.h"
#include "MovePlatform.h"
#include "Gate.h"
#include "Weapon.h"
#include "Bat.h"
#include "MadusaHead.h"
#include "Trap.h"
#include "Ghost.h"
#include "BonePillar.h"
#include "BossLv2.h"
#include "Pleaman.h"
#include "Skeleton.h"
#include "Raven.h"
#include "Bosslv3.h"

using namespace std;


class ObjManager
{
private:
	vector<int*> InfoObj; //
	vector<int*> InfoObjTemp;
	QuadTree* quadTree;
	list<int> listID;
	vector<Object*> listObj;
	vector<Enemy*> listEnemy;
	int idsize = 0;
	RECT rect;
	ifstream f;
public:
	bool Isclear;
	int Frozen;
	ObjManager() 
	{
		quadTree = new QuadTree();
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
			lTemp[6] = 0;
			//add info object	
			InfoObj.push_back(lTemp);
		}
	}
	
	void Init(char* fileGameObj, char* fileQuadTree)
	{
		LoadFileInfo(fileGameObj);
		quadTree->GetQuadTreeFromFile(fileQuadTree);
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
	
	void GetListIDFromquadTree(RECT rectCamera)
	{
		rect = rectCamera;
		listID.clear();
		quadTree->GetlistObj(quadTree->Root, rectCamera, listID);
		idsize = listID.size();		

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
			case GroundMovingPlatform:
				obj = new MovePlatform(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case GroundTrident:
				obj = new Trap(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case BossLv2:
				obj = new BossLV2(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case BossLv3:
				obj = new BosslV3(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyZombie:
				break;
			case EnemyBlackLeopard:
				obj = new Enemy(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyVampireBat:
				obj = new Bat(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyMedusa:
				obj = new MadusaHead(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyAxeMan:
				break;
			case EnemyDragonSkullCannon:
				obj = new BonePillar(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyBlackNight:
				obj = new SpearGuard(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyWhiteSkeleton:
				obj = new Skeleton(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyGhost:
				obj = new Ghost(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyRaven:
				obj = new Raven(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			case EnemyPleaman:
				obj = new Pleaman(t[0], t[1], t[2], t[3], t[4], t[5]);
				break;
			default:
				break;
			}			

			listEnemy.push_back(obj);
		}
	}
	
	void GetListObjFromQuadTree()
	{
		//get list obj game
		//bien phu
		vector<int> tempEnemy;
		std::list<int>::iterator it;
		int *t = new int[7];
		int j;
		Type _type;
		for (int i = 0; i < listObj.size(); i++)
		{
			delete listObj[i];
		}
		listObj.clear();
		for (it = listID.begin(); it != listID.end(); it++)
		{
			t = InfoObj[*it];
			RECT check{ t[2],t[3], t[2] + t[4],t[3] + t[5] };
			if (Collision::CheckCollison(rect, check))
			{
				if (t[1] >= 600 && t[1] != 615 && t[1] !=611)
				{
					Object* obj = new Object(t[0], t[1], t[2], t[3], t[4], t[5]);
					listObj.push_back(obj);
				}
				else
				{
					//Load id enemy
					tempEnemy.push_back(*it);
				}
			}
		}

		//loai bo pt trung
		if(!tempEnemy.empty())
			for (int i = 0; i < tempEnemy.size() - 1; i++)
			{
				for (int j = i + 1; j < tempEnemy.size(); j++)
				{
					if (tempEnemy[i] == tempEnemy[j])
					{
						tempEnemy.erase(tempEnemy.begin() + j);
						j--;
					}
									
				}
				//if (!tempEnemy.empty())
					
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
				for (int r = i+1; r < listEnemy.size(); r++)
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
				if (check == false && Collision::AABBCheck(listEnemy[i]->GetBox(),Box::ConvertRECT(rect)) == false)
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


		//else
		//{
		//	for (int i = 0; i < listObj.size(); i++)
		//	{
		//		int j = 0;
		//		int size = listID.size();
		//		for (it = listID.begin(); it != listID.end(); it++)
		//		{
		//			j++;
		//			if (*it == listObj[i]->GetID())
		//			{
		//				//delete &it;
		//				listID.erase(it);
		//				break;
		//			}				
		//		}				
		//		if (j==size)
		//		{
		//			delete listObj[i];
		//			listObj.erase(listObj.begin() + i);
		//		}
		//	}
		//	for (it = listID.begin(); it != listID.end(); it++)
		//	{
		//		for (int i = 0; i < InfoObj.size(); i++)
		//		{
		//			t = InfoObj[i];
		//			if (*it == t[0])
		//			{
		//				RECT check{ t[2],t[3], t[2] + t[4],t[3] + t[5] };
		//				if (Collision::CheckCollison(rect, check))
		//				{
		//					Object* obj = new Object(t[0], t[1], t[2], t[3], t[4], t[5]);
		//					listObj.push_back(obj);
		//				}
		//			}
		//		}
		//	}
		//}
				
	}

	void UpDate(RECT rectCamera, vector<Object> &listItem,int DeltaTime,Box simon)
	{
		GetListIDFromquadTree(rectCamera);
		GetListObjFromQuadTree();
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
		
		//Update animation
		BigCandel::GetStaticObj()->Update();
		SmallCandle::GetStaticObj()->Update();
		//Draw gate
		CGate::GetStaticObj()->Draw();
		if (Isclear)
		return;
		Type _type;
		//Draw object
		for (int i = 0; i < listObj.size(); i++)
		{			
			_type = (Type)listObj[i]->GetType();
			switch (_type)
			{
			case GroundBigLightHeart:
				BigCandel::GetStaticObj()->Draw(listObj[i]->GetX(), listObj[i]->GetY());
				break;
			case GroundBigLightRod:
				break;
			case GroundBigLightDagger:
				break;
			case GroundBigLight:
				break;				
			case GroundStair:
				break;
			case GroundUnknow:
				break;
			case ground:
				break;			
			case Gate:
				break;
			case Ground2:
				//Tile::GetStaticObj()->Draw(listObj[i]->GetX(), listObj[i]->GetY(), 0);
				break;
			case GroundStair2:
				//Stair::GetStaticObj()->Draw(listObj[i]->GetX(), listObj[i]->GetY());
				
				break;
			case GroundStiar3:
				//TopStair::GetStaticObj()->Draw(listObj[i]->GetX(), listObj[i]->GetY());
				break;
			case ItemRoast:
				if (InfoObj[listObj[i]->GetID()][6] == 1)
					Item::GetStaticObj()->DrawBreakWall(listObj[i]);
				break;
			case ItemDoubleShot:
				if (InfoObj[listObj[i]->GetID()][6] == 1)
					Item::GetStaticObj()->DrawBreakWall(listObj[i]);
				break;
			case ItemTripbleShot:
				if (InfoObj[listObj[i]->GetID()][6] == 1)
					Item::GetStaticObj()->DrawBreakWall(listObj[i]);
				break;
			case ItemHidden:
				if (InfoObj[listObj[i]->GetID()][6] == 1)
					Item::GetStaticObj()->DrawBreakWall(listObj[i]);
				break;
			case ItemCrown:
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
			case GroundMovingPlatform:
				EnemyRender::GetStaticObj()->DrawMovePlatform(listEnemy[i]->GetX(), listEnemy[i]->GetY());
				break;
			case GroundTrident:
				listEnemy[i]->Draw();
				break;
			case BossLv2:
				listEnemy[i]->Draw();
				break;
			case BossLv3:
				listEnemy[i]->Draw();
				break;
			case EnemyVampireBat:
				EnemyRender::GetStaticObj()->DrawBat(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case EnemyMedusa:
				EnemyRender::GetStaticObj()->DrawMedusaHead(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case EnemyDragonSkullCannon:
				listEnemy[i]->Draw();
				break;
			case EnemyBlackNight:
				EnemyRender::GetStaticObj()->DrawSpearGuard(listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->GetIndex(), listEnemy[i]->GetDirect());
				break;
			case EnemyWhiteSkeleton:
				listEnemy[i]->Draw();
				break;
			case EnemyGhost:
				listEnemy[i]->Draw();
				break;
			case EnemyRaven:
				listEnemy[i]->Draw();
				break;
			case EnemyPleaman:
				listEnemy[i]->Draw();
				break;
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
			if (listObj[i]->GetType() == 616)
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
					case GroundMovingPlatform:
						tempBox = listEnemy[j]->GetBox();
						tempBox.x = listEnemy[j]->GetBox().x - 10;
						tempBox.w = listEnemy[j]->GetBox().w + 10;
						if (Collision::HitTheWall(tempBox, listObj[i]->GetBox()))
						{
							listEnemy[j]->turn *= -1;
						}
						break;
					case BossLv2:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case BossLv3:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case EnemyZombie:
						break;
					case EnemyBlackLeopard:
						break;
					case EnemyVampireBat:
						break;
					case EnemyMedusa:
						break;
					case EnemyFishMan:
						break;
					case EnemyAxeMan:
						break;
					case EnemyDragonSkullCannon:
						break;
					case EnemyBlackNight:
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
					case EnemyWhiteSkeleton:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case EnemyPleaman:
						listEnemy[j]->CollisionWithObj(listObj[i]);
						break;
					case EnemyRaven:
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
		//if (quadTree != NULL) delete quadTree; 
		f.close();
	}
};
#endif // !_OBJMANAGER_H_




