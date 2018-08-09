#pragma once
#include "BaseObject.h"
#include <d3d9.h>
#include <vector>
using namespace std;

class Effect :public BaseObject
{
	static Effect* pStaticObj;
	vector<D3DXVECTOR3> listEffect;
public:
	Effect();
	D3DXVECTOR3 obj;
	void Init();
	void Add(Object* obj);
	static Effect* GetStaticObj();
	void Draw();
	~Effect();
};

