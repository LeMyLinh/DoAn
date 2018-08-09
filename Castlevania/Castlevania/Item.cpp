#include "Item.h"
#include "Collision.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>
using namespace std;

Item* Item::pStaticObj = 0;

Item::Item()
{
	beakWall = new Object();

	Heart = new GTexture();
	bigHeart = new GTexture();
	morningStar = new GTexture();
	Roast = new GTexture();
	rosary = new GTexture();
	treasureChest = new GTexture();
	Invincible = new GTexture();
	Hidden = new GTexture();
	doubleShot = new GTexture();
	tripleShot = new GTexture();	
	lvUp = new GTexture();
	knife = new GTexture();
	Bomerang = new GTexture();
	boom = new GTexture();
	axe = new GTexture();
	BreakWall = new GTexture();
	iconDoubleShot = new GTexture();
	iconTripbleShot = new GTexture();
	//
	b = false;
}

void Item::Init()
{
	//L"Resources/item/
	Heart->loadTextTureFromFile(L"Resources/item/0.png",D3DCOLOR_XRGB(255,0,255));
	bigHeart->loadTextTureFromFile(L"Resources/item/1.png", D3DCOLOR_XRGB(255, 0, 255));
	GTexture* money = new GTexture();
	money->loadTextTureFromFile(L"Resources/item/2.png", D3DCOLOR_XRGB(255, 0, 255));
	Bag = new GSprite(money, 3, 1, 0);
	morningStar->loadTextTureFromFile(L"Resources/item/3.png", D3DCOLOR_XRGB(255, 0, 255));
	Roast->loadTextTureFromFile(L"Resources/item/10.png", D3DCOLOR_XRGB(255, 0, 255));
	doubleShot->loadTextTureFromFile(L"Resources/item/11.png", D3DCOLOR_XRGB(255, 0, 255));
	tripleShot->loadTextTureFromFile(L"Resources/item/12.png", D3DCOLOR_XRGB(255, 0, 255));
	knife->loadTextTureFromFile(L"Resources/item/4.png", D3DCOLOR_XRGB(255, 0, 255));
	Bomerang->loadTextTureFromFile(L"Resources/item/8.png", D3DCOLOR_XRGB(255, 0, 255));
	axe->loadTextTureFromFile(L"Resources/item/7.png", D3DCOLOR_XRGB(255, 0, 255));
	boom->loadTextTureFromFile(L"Resources/item/9.png", D3DCOLOR_XRGB(255, 0, 255));
	rosary->loadTextTureFromFile(L"Resources/item/6.png", D3DCOLOR_XRGB(255, 0, 255));
	GTexture* ttcrown = new GTexture();
	ttcrown->loadTextTureFromFile(L"Resources/item/Crown1.png", D3DCOLOR_XRGB(0, 0, 0));
	crown = new GSprite(ttcrown, 4, 1, 1000/20);
	doubleShot->loadTextTureFromFile(L"Resources/item/11.png", D3DCOLOR_XRGB(255, 0, 255));
	tripleShot->loadTextTureFromFile(L"Resources/item/12.png", D3DCOLOR_XRGB(255, 0, 255));
	BreakWall->loadTextTureFromFile(L"Resources/ground/hidden.png", D3DCOLOR_XRGB(255, 1, 255));
	iconDoubleShot->loadTextTureFromFile(L"Resources/item/11-2.png", D3DCOLOR_XRGB(255, 0, 255));
	iconTripbleShot->loadTextTureFromFile(L"Resources/item/12-2.png", D3DCOLOR_XRGB(255, 0, 255));
	GTexture* ttspriritBall = new GTexture();
	ttspriritBall->loadTextTureFromFile(L"Resources/item/13.png", D3DCOLOR_XRGB(255, 0, 255));
	spriritBall = new GSprite(ttspriritBall, 2, 1, 1000 / 20);
	StopWatch = new GTexture();
	StopWatch->loadTextTureFromFile(L"Resources/item/5.png", D3DCOLOR_XRGB(255, 0, 255));
}

void Item::Update(int Delta)
{
	for (int i = 0; i < listItem.size(); i++)
	{
		if (listItem[i].turn < 25)
		{
			listItem[i].turn++;
			continue;
		}
		if (listItem[i].GetType() == 600)
		{
			if (listItem[i].GetX() == listItem[i].index)
				listItem[i].SetVec(1, 1);
			if (listItem[i].GetX() >= listItem[i].index + 25)
				listItem[i].SetVec(-1, 1);
			if (listItem[i].GetX() <= listItem[i].index - 25)
				listItem[i].SetVec(1, 1);
		}
		else
		{
			listItem[i].SetVy(listItem[i].GetBox().vy*1.12);
		}
		if (listItem[i].temp >= 0)
		{
			if (listItem[i].GetType()==630)
			{
				if (listItem[i].temp >= 5000)
				{
					listItem.erase(listItem.begin() + i);
					continue;
				}
				else
				{
					listItem[i].temp += Delta;
				}
			}
			else
			{
				if (listItem[i].temp >= 2500)
				{
					listItem.erase(listItem.begin() + i);
					continue;
				}
				else
				{
					listItem[i].temp += Delta;
				}
			}
			
		}
		listItem[i].Update();
	}
}


Item * Item::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new Item();
	return pStaticObj;
}


void Item::Add(Object * o, int power)
{
	Object obj;
	obj.SetObj(o->GetID(), o->GetType(), o->GetX(), o->GetY(), o->GetBox().w, o->GetBox().h);
	if (obj.GetType() == 600 && power<2)
	{
		srand(time(0));
		int r0 = rand() % 2;
		if (r0 == 1)
		{
			obj.SetType(621);
		}
	}
	if (obj.GetType() == 600)
	{
		obj.index = obj.GetX();
	}		
	obj.temp = -1;
	obj.SetVy(3);
	obj.turn = 0;
	listItem.push_back(obj);
}

void Item::Draw(int Delta)
{
	if (listItem.empty())
		return;
	Type _type;
	for (int i = 0; i < listItem.size(); i++)
	{
		if (listItem[i].turn < 25)
		{
			listItem[i].turn++;
			continue;
		}
		_type = (Type)listItem[i].GetType();
		switch (_type)
		{
		case GroundBigLightHeart:
			bigHeart->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundBigLightRod:
			break;
		case GroundBigLightDagger:
			break;
		case GroundBigLight:
			break;
		case GroundSmallLightAxe:	
			axe->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightBoomerang:
			Bomerang->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightCross:
			rosary->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightDoubleShot:
			break;
		case GroundSmallLightFireBomb:
			boom->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightRandom:
			StopWatch->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightHeart:
			bigHeart->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightSmallHeart:
			Heart->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightRod:
			morningStar->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightKnife:
			knife->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case GroundSmallLightBag1000:
			Bag->Draw(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2, 0);
			break;
		case GroundSmallLightBag700:
			Bag->Draw(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2, 1);
			break;
		case GroundSmallLightBag400:
			Bag->Draw(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2, 2);
			break;
		case ItemRoast:
			Roast->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case ItemDoubleShot:
			doubleShot->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case ItemTripbleShot:
			tripleShot->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case ItemHidden:
			break;
		case ItemCrown:
			if (b)
			{
				crown->SetFormat(D3DXVECTOR2(2, 2), 0, 1);
				crown->Draw(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
				crown->Update(Delta);
			}
			break;
		default:
			break;
		}		
	}
}

vector<Object> Item::GetListItem()
{
	return listItem;
}

void Item::RemoveAt(int i)
{
	listItem.erase(listItem.begin() + i);
}

void Item::setXY(int i, int x, int y)
{
	listItem[i].SetX(x);
	listItem[i].SetY(y);
	listItem[i].SetVy(3);
}

void Item::CollisionHandle(Object* o)
{
	if ((o->GetType() >= 626 && o->GetType() <= 630))
		return;
	for (int i = 0; i < listItem.size(); i++)
	{
		Box b = listItem[i].GetBox();
		b.h += b.vy;
		if (Collision::IsStandOnGround(b, o->GetBox()))
		{
			listItem[i].SetVec(0, 0);
			listItem[i].SetY(o->GetY() - listItem[i].Heigt);
			if (listItem[i].temp == -1&&listItem[i].GetType()!=30)
				listItem[i].temp = 0;
		}
		
	}
}

void Item::DrawBreakWall(Object* o)
{
	BreakWall->RenderTexture(o->GetX() + 16, o->GetY() + 16);
}


Item::~Item()
{
}
