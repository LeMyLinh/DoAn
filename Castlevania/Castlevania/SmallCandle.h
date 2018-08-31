#pragma once
#include "BaseObject.h"

class SmallCandle :public BaseObject
{
private:
	static SmallCandle* pStaticObj;
public:
	SmallCandle();
	void Init();
	static SmallCandle* GetStaticObj();
	void Update();
	void Draw(int _x, int _y);
	~SmallCandle();
};

