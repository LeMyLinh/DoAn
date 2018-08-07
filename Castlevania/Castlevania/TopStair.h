#pragma once
#include "BaseObject.h"
class TopStair :public BaseObject
{
	static TopStair* pStaticObj;
public:
	TopStair();
	void Init();
	static TopStair* GetStaticObj();
	void Draw(int _x, int _y);
	~TopStair();
};

