#pragma once
#include "BaseObject.h"


class CGate:public BaseObject
{
protected:
	static CGate* pStaticObj;
	int x;
	int y;
	int index;
	bool IsDraw;
public:
	CGate();
	void Init();
	static CGate* GetStaticObj();
	void Update(int _x, int _y, int _index);
	void Draw();
	~CGate();
};

