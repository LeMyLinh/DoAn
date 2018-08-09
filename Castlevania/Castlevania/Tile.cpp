#include "Tile.h"

Tile* Tile::pStaticObj = 0;

Tile::Tile()
{
}

void Tile::Init()
{
	BaseObject::LoadResource(L"Resources/ground/2-2.png", 1, 1, 0);
}


Tile* Tile::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new Tile();
	return pStaticObj;
}

void Tile::Draw(int _x, int _y, int _index)
{
	Sprite->SelectIndex(_index);
	Sprite->Draw(_x + Sprite->_FrameWidth / 2, _y + Sprite->_FrameHeight / 2);
}



Tile::~Tile()
{
}
