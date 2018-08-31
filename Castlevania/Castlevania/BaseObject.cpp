#include "BaseObject.h"
#include "GTexture.h"


BaseObject::BaseObject()
{
}

BaseObject::BaseObject(int _id, int _type, int _x, int _y, int _Width, int _Height) :Object(_id, _type, _x, _y, _Width, _Height)
{
	vecX = 0;
	vecY = 0;
}

void BaseObject::LoadResource(LPCWSTR resourceFile, int cols, int rows, int detalTime)
{
	GTexture* texture = new GTexture();
	texture->loadTextTureFromFile(resourceFile, D3DCOLOR_XRGB(255, 0, 255));
	Sprite = new GSprite(texture, cols, rows, detalTime);
}

void BaseObject::Update()
{
}

void BaseObject::Draw()
{
}

BaseObject::~BaseObject()
{
	if (Sprite != NULL) delete Sprite;
}
