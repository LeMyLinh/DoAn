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
	Heart = new GTexture();
	bigHeart = new GTexture();
	morningStar = new GTexture();
	rosary = new GTexture();
	treasureChest = new GTexture();
	Invincible = new GTexture();
	Hidden = new GTexture();
	doubleShot = new GTexture();
	tripleShot = new GTexture();	
	Bomerang = new GTexture();
	boom = new GTexture();
	axe = new GTexture();
	iconDoubleShot = new GTexture();
	iconTripbleShot = new GTexture();
	//
	b = false;
}

void Item::Init()
{
	Heart->loadTextTureFromFile(L"Resources/item/0.png",D3DCOLOR_XRGB(255,0,255));
	bigHeart->loadTextTureFromFile(L"Resources/item/1.png", D3DCOLOR_XRGB(255, 0, 255));
	GTexture* money = new GTexture();
	money->loadTextTureFromFile(L"Resources/item/2.png", D3DCOLOR_XRGB(255, 0, 255));
	Bag = new GSprite(money, 3, 1, 0);
	morningStar->loadTextTureFromFile(L"Resources/item/3.png", D3DCOLOR_XRGB(255, 0, 255));
	doubleShot->loadTextTureFromFile(L"Resources/item/11.png", D3DCOLOR_XRGB(255, 0, 255));
	tripleShot->loadTextTureFromFile(L"Resources/item/12.png", D3DCOLOR_XRGB(255, 0, 255));
	Bomerang->loadTextTureFromFile(L"Resources/item/8.png", D3DCOLOR_XRGB(255, 0, 255));
	axe->loadTextTureFromFile(L"Resources/item/7.png", D3DCOLOR_XRGB(255, 0, 255));
	boom->loadTextTureFromFile(L"Resources/item/9.png", D3DCOLOR_XRGB(255, 0, 255));
	rosary->loadTextTureFromFile(L"Resources/item/6.png", D3DCOLOR_XRGB(255, 0, 255));
	doubleShot->loadTextTureFromFile(L"Resources/item/11.png", D3DCOLOR_XRGB(255, 0, 255));
	tripleShot->loadTextTureFromFile(L"Resources/item/12.png", D3DCOLOR_XRGB(255, 0, 255));
	iconDoubleShot->loadTextTureFromFile(L"Resources/item/11-2.png", D3DCOLOR_XRGB(255, 0, 255));
	iconTripbleShot->loadTextTureFromFile(L"Resources/item/12-2.png", D3DCOLOR_XRGB(255, 0, 255));
	GTexture* ttspriritBall = new GTexture();
	ttspriritBall->loadTextTureFromFile(L"Resources/item/13.png", D3DCOLOR_XRGB(255, 0, 255));
	spriritBall = new GSprite(ttspriritBall, 2, 1, 1000 / 20);
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
		if (listItem[i].GetType() == SMALLHEART)
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
	if (obj.GetType() == SMALLHEART && power<2)
	{
		srand(time(0));
		int r0 = rand() % 2;
		if (r0 == 1)
		{
			obj.SetType(621);
		}
	}
	if (obj.GetType() == SMALLHEART)
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
		case AXE:	
			axe->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case CROSS:
			Bomerang->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case FIREBOMB:
			boom->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case LARGEHEART:
			bigHeart->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case SMALLHEART:
			Heart->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case BAG1000:
			Bag->Draw(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2, 0);
			break;
		case BAG700:
			Bag->Draw(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2, 1);
			break;
		case BAG400:
			Bag->Draw(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2, 2);
			break;
		case DOUBLESHOT:
			doubleShot->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
			break;
		case TRIPLESHOT:
			tripleShot->RenderTexture(listItem[i].GetX() + listItem[i].GetBox().w / 2, listItem[i].GetY() + listItem[i].GetBox().h / 2);
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
	for (int i = 0; i < listItem.size(); i++)
	{
		Box b = listItem[i].GetBox();
		b.h += b.vy;
		if (Collision::IsStandOnGround(b, o->GetBox()))
		{
			listItem[i].SetVec(0, 0);
			listItem[i].SetY(o->GetY() - listItem[i].Heigt);
			if (listItem[i].temp == -1 && listItem[i].GetType()!=30)
				listItem[i].temp = 0;
		}
		
	}
}

void Item::DrawBreakWall(Object* o)
{
}


Item::~Item()
{
}
