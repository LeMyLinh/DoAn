#include "MovePlatform.h"

MovePlatform::MovePlatform()
{
}

MovePlatform::MovePlatform(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height) 
{
	bound = 50;
	xOld = x;
	turn = 1;
	vecX = turn * 1.5;
}

void MovePlatform::Update(Box RectCamera, Box simon, int Deltatime)
{

	if (vecX > 0)
	{
		if (x >= xOld + bound)
		{
			turn *= -1;
		}
	}
	else
	{
		if (x <= xOld - bound)
		{
			turn *= -1;			
		}
	}
	vecX = turn * 1.5;
	x += vecX;
}


MovePlatform::~MovePlatform()
{
}
