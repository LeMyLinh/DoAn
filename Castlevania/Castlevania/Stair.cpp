#include "Stair.h"

Stair* Stair::pStaticObj = 0;


void Stair::Init()
{
}


Stair* Stair::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new Stair();
	return pStaticObj;
}

void Stair::Draw(int _x, int _y)
{
}


Stair::Stair()
{
}


Stair::~Stair()
{
}
