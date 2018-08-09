#include "Effect.h"

Effect* Effect::pStaticObj = 0;


Effect::Effect()
{
	
}

void Effect::Init()
{
	BaseObject::LoadResource(L"Resources/other/1.png", 3, 1, 1000/30);
}

void Effect::Add(Object * obj)
{
	D3DXVECTOR3 temp{ obj->GetX() + obj->GetBox().w / 2,obj->GetY() + obj->GetBox().h / 2,0 };
	listEffect.push_back(temp);
}

Effect * Effect::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new Effect();
	return pStaticObj;
}


void Effect::Draw()
{
	if (listEffect.empty())
		return;
	for (int i = 0; i < listEffect.size(); i++)
	{
		//delete obj
		if (listEffect[i].z == 6)
		{
			listEffect.erase(listEffect.begin() + i);
			return;
		}
		//draw
		Sprite->Draw((int)listEffect[i].x, (int)listEffect[i].y, (int)(listEffect[i].z++)%3);
	}
	
}

Effect::~Effect()
{
}
