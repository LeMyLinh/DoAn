#include "TopStair.h"

TopStair* TopStair::pStaticObj = 0;


TopStair::TopStair()
{
}

void TopStair::Init()
{
}

TopStair * TopStair::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new TopStair();
	return pStaticObj;
}

void TopStair::Draw(int _x, int _y)
{
}


TopStair::~TopStair()
{
}
