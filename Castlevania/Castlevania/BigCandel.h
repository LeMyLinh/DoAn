#pragma once
#include "BaseObject.h"

class BigCandel :public BaseObject
{
	static BigCandel* pStaticObj;
public:
	BigCandel();
	void Init();
	static BigCandel* GetStaticObj();
	void Update();
	void Draw(int _x, int _y);
	~BigCandel();
};

