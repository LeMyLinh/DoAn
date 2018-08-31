#include "Item.h"
#include "Collision.h"
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <math.h>
#include "Constant.h"

using namespace std;

Item* Item::pStaticObj = 0;

Item::Item()
{
	Heart = new GTexture();
	bigHeart = new GTexture();
	morningStar = new GTexture();
	rosary = new GTexture();
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
	Heart->loadTextTureFromFile(SMALLHEART_IMAGE , COLOR_LOAD_TEXTURE);
	bigHeart->loadTextTureFromFile(LARGEHEART_IMAGE, COLOR_LOAD_TEXTURE);
	GTexture* money = new GTexture();
	money->loadTextTureFromFile(BAGMONEY_IMAGE, COLOR_LOAD_TEXTURE);
	Bag = new GSprite(money, 3, 1, 0);
	morningStar->loadTextTureFromFile(MORNINGSTAR_IMAGE, COLOR_LOAD_TEXTURE);
	doubleShot->loadTextTureFromFile(DOUBLESHOT_IMAGE, COLOR_LOAD_TEXTURE);
	tripleShot->loadTextTureFromFile(TRIPLESHOT_IMAGE, COLOR_LOAD_TEXTURE);
	Bomerang->loadTextTureFromFile(BOMERANG_IMAGE, COLOR_LOAD_TEXTURE);
	axe->loadTextTureFromFile(AXE_IMAGE, COLOR_LOAD_TEXTURE);
	boom->loadTextTureFromFile(FIREBOMB_IMAGE, COLOR_LOAD_TEXTURE);
	rosary->loadTextTureFromFile(ROSARY_IMAGE, COLOR_LOAD_TEXTURE);
	iconDoubleShot->loadTextTureFromFile(ICON_DOUBLESHOT, COLOR_LOAD_TEXTURE);
	iconTripbleShot->loadTextTureFromFile(ICON_TRIPLESHOT, COLOR_LOAD_TEXTURE);

	GTexture* ttspriritBall = new GTexture();
	ttspriritBall->loadTextTureFromFile(SPRIRITBALL, COLOR_LOAD_TEXTURE);
	spriritBall = new GSprite(ttspriritBall, COL_OF_SPRIRIT, ROW_OF_SPRIRIT, TIME_ANIM_SPRIRIT);
}

void Item::Update(int Delta)
{
	for (int i = 0; i < listItem.size(); i++)
	{
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
		case LARGEHEART_BIGCANDLE:
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
