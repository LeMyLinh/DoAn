#include "Object.h"

int Object::GetIndex()
{
	return index;
}

int Object::GetDirect()
{
	return turn;
}

Object::Object()
{
	x = 0;
	y = 0;
	Type = 0;
	id = 0;
	Width = 0;
	Heigt = 0;
	vecX = 0;
	vecY = 0;
	turn = 1;
	index = 0;
	IsDie = false;
}

Object::Object(int _id, int _type, int _x, int _y, int _Width, int _Height)
{
	x = _x;
	y = _y;
	Type = _type;
	id = _id;
	Width = _Width;
	Heigt = _Height;
	vecX = 0;
	vecY = 0;
	turn = 1;
	index = 0;
	IsDie = false;
}

void Object::SetObj(int _id, int _type, int _x, int _y, int _Width, int _Height)
{
	x = _x;
	y = _y;
	Type = _type;
	id = _id;
	Width = _Width;
	Heigt = _Height;
	vecX = 0;
	vecY = 0;
	turn = 1;
	index = 0;
	IsDie = false;
}

void Object::Update()
{
	x += vecX;
	y += vecY;
}

int Object::GetID()
{
	return id;
}

int Object::GetX()
{
	return x;
}

int Object::GetY()
{
	return y;
}

int Object::GetType()
{
	return Type;
}

void Object::SetX(int v)
{
	x = v;
}

void Object::SetY(int v)
{
	y = v;
}

void Object::SetVec(float vx, float vy)
{
	vecX = vx;
	vecY = vy;
}

void Object::SetVx(float vx)
{
	vecX = vx;
}

void Object::SetVy(float vy)
{
	vecY = vy;
}

void Object::SetType(int type)
{
	this->Type = type;
}

Box Object::GetBox()
{
	Box Result;
	Result.x = x;
	Result.y = y;
	Result.w = Width;
	Result.h = Heigt;
	Result.vx = vecX;
	Result.vy = vecY;
	return Result;
}


Object::~Object()
{
}
