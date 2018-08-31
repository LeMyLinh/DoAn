#ifndef _COLLISION_H_
#define _COLLISION_H_

#include <d3d9.h>
#include "Box.h"

class Collision
{
public:
	Collision();
	static bool CheckCollison(RECT r1,RECT r2);
	static float SweptAABB(Box b1, Box b2, float & normalx, float & normaly);
	static bool IsStandOnGround(Box b1, Box b2);
	static bool AABBCheck(Box b1, Box  b2);
	static int HitTheWall(Box b1, Box b2);
	~Collision();
};
#endif



