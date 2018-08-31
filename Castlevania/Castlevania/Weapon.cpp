#include "Weapon.h"
#include <math.h>
#include "Constant.h"

Weapon* Weapon::pStaticObj = 0;

Weapon::Weapon()
{
	typeWP = 2;
	IsFight = false;
	IsReady = true;
	damage = 1;
	time = 0;
	localTime = 0;
}

bool Weapon::Ready()
{
	if (typeWP == 0)
		return false;
	if (IsReady == false)
		return false;
	return true;
}

void Weapon::Init()
{
	GTexture* tBomerang = new GTexture(); //2
	GTexture* tAxe = new GTexture(); //3
	tBomerang->loadTextTureFromFile(BOMERANG_IMAGE, COLOR_LOAD_TEXTURE);
	tAxe->loadTextTureFromFile(AXEWEAPON_IMAGE, COLOR_LOAD_TEXTURE);

	Bomerang = new GSprite(tBomerang, 3, 1, 1000 / 10);
	Axe = new GSprite(tAxe, 4, 1, 100);
}

Weapon * Weapon::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new Weapon();
	return pStaticObj;
}

void Weapon::CheckWeaponInItem(Object item)
{
	Type _type;
	_type = (Type)item.GetType();
	switch (_type)
	{
	case AXE:
		typeWP = 3;
		damage = 2;
		break;
	case CROSS:
		typeWP = 2;
		damage = 2;
		break;
	default:
		break;
	}
}

void Weapon::Fight(int _x, int _y, int turn, BlackBoard* blackBoard)
{
	blackBoard->HeartValue--;
	Object obj;
	obj.SetX(_x);
	obj.SetY(_y);
	obj.turn = turn;
	obj.temp = turn;
	D3DXVECTOR2 i;
	switch (typeWP)
	{
	case 2:
		obj.Width = Bomerang->_FrameWidth;
		obj.Heigt = Bomerang->_FrameHeight;
		break;
	case 3:
		i.x = obj.GetX();
		i.y = 90/*obj.GetY()*/;
		tami.push_back(i);
		obj.SetVx(4 * turn);
		obj.Width = Axe->_FrameWidth;
		obj.Heigt = Axe->_FrameHeight;
		break;
	default:
		break;
	}
	listWeapon.push_back(obj);
}

void Weapon::Update(RECT camera, BlackBoard* blackBoard, Box Simon, int DeltaTime)
{
	if (blackBoard->HeartValue == 0)
		IsReady = false;

	else
	{
		IsReady = true;
	}
	if (typeWP == 0)
		return;
	switch (typeWP)
	{
	case 2:
		UpdateBoomerang(camera, Simon);
		break;
	case 3:
		UpdateAxe(camera, DeltaTime);
		break;
	default:
		break;
	}
	for (int i = 0; i < listWeapon.size(); i++)
	{
		UpdateIndex(listWeapon[i].index, DeltaTime);
	}

}


void Weapon::UpdateBoomerang(RECT camera, Box Simon)
{
	for (int i = 0; i < listWeapon.size(); i++)
	{
		if (listWeapon[i].turn == 1)
		{
			if (listWeapon[i].GetX() >= camera.right)
				listWeapon[i].temp = -listWeapon[i].turn;
			if (listWeapon[i].GetX() <= camera.left || Collision::AABBCheck(listWeapon[i].GetBox(), Simon))
			{
				listWeapon.erase(listWeapon.begin() + i);
				continue;
			}
		}
		else if (listWeapon[i].turn == -1)
		{
			if (listWeapon[i].GetX() <= camera.left)
				listWeapon[i].temp = -listWeapon[i].turn;
			if (listWeapon[i].GetX() >= camera.right || Collision::AABBCheck(listWeapon[i].GetBox(), Simon) && listWeapon[i].temp == -listWeapon[i].turn)
			{
				listWeapon.erase(listWeapon.begin() + i);
				continue;
			}
		}
		listWeapon[i].SetVx(listWeapon[i].temp * 6);
		listWeapon[i].SetVy(0);
		listWeapon[i].SetX(listWeapon[i].GetX() + listWeapon[i].temp * 6);
	}
}

void Weapon::UpdateAxe(RECT camera, int DeltaTime)
{
	for (int i = 0; i < listWeapon.size(); i++)
	{
		if (Collision::AABBCheck(listWeapon[i].GetBox(), Box::ConvertRECT(camera)) == false)
		{
			listWeapon.erase(listWeapon.begin() + i);
			tami.erase(tami.begin() + i);
			continue;
		}
		listWeapon[i].SetX(listWeapon[i].GetX() + listWeapon[i].GetBox().vx);

		if (listWeapon[i].temp == listWeapon[i].turn)
		{
			tami[i].y -= 3;
			if (tami[i].y <= 3)
				listWeapon[i].temp *= -1;
		}
		listWeapon[i].SetVy(sin(tami[i].y)*(130));

		listWeapon[i].SetY(listWeapon[i].GetY() + listWeapon[i].GetBox().vy);

	}
}


void Weapon::Collison(Object * obj, int DeltaTime)
{
	for (int i = 0; i < listWeapon.size(); i++)
	{
		if (typeWP == 4 && Collision::AABBCheck(listWeapon[i].GetBox(), obj->GetBox()))
		{
			time += DeltaTime;
			if (listWeapon[i].index >= 1)
			{
				if (time >= 1000 / 3)
				{
					time = 0;
					listWeapon[i].index++;
				}
			}
			else
				listWeapon[i].index++;

			//UpdateIndex(listWeapon[i].index, DeltaTime);
			listWeapon[i].SetVx(0);
			listWeapon[i].SetVy(0);
		}
	}

}

bool Weapon::Check(Object * obj)
{
	if (obj->IsDie)
		return false;
	/*float normalx, normaly;
	float colisionTime;*/
	for (int i = 0; i < listWeapon.size(); i++)
	{
		//colisionTime = Collision::SweptAABB(listWeapon[i].GetBox(), obj->GetBox(),normalx,normaly);
		if (Collision::AABBCheck(listWeapon[i].GetBox(), obj->GetBox()))
		{
			if (typeWP == 1)
				listWeapon.erase(listWeapon.begin() + i);
			if (typeWP == 4 && listWeapon[i].index == 0)
				return false;
			return true;
		}
	}

	return false;
}

void Weapon::Draw()
{
	if (typeWP == 0)
		return;
	for (int i = 0; i < listWeapon.size(); i++)
	{
		switch (typeWP)
		{
		case 2:
			Bomerang->Draw(listWeapon[i].GetX() + listWeapon[i].GetBox().w / 2, listWeapon[i].GetY() + listWeapon[i].GetBox().h / 2, listWeapon[i].index);
			break;
		case 3:
			Axe->Draw(listWeapon[i].GetX() + listWeapon[i].GetBox().w / 2, listWeapon[i].GetY() + listWeapon[i].GetBox().h / 2, listWeapon[i].index);
			break;
		default:
			break;
		}
	}
}

void Weapon::UpdateIndex(int &index, int delta)
{
	localTime += delta;
	if (localTime >= 1000 / 15)
	{
		localTime = 0;
		switch (typeWP)
		{
		case 2:
			index++;
			if (index > 2 || index < 0)
				index = 0;
			break;
		case 3:
			index++;
			if (index > 3 || index < 0)
				index = 0;
			break;
		default:
			break;
		}
	}
}

void Weapon::Reset()
{
	typeWP = 0;
}



Weapon::~Weapon()
{
}
