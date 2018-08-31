#pragma once
#include "BaseObject.h"

class Stair :public BaseObject
{
private:
	static Stair* pStaticObj;
public:
	Stair();
	void Init();
	static Stair* GetStaticObj();
	void Draw(int _x, int _y);
	~Stair();
};

