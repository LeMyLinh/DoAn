#pragma once
#include "BaseObject.h"

class BigCandle : public BaseObject
{
	static BigCandle* pStaticObj;
public:
	BigCandle();
	void Init();
	static BigCandle* GetStaticObj();
	void Update();
	void Draw(int _x, int _y);
	~BigCandle();
};

