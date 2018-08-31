#pragma once
#include "BaseObject.h"

class BlockGate : public BaseObject
{
private:
	static BlockGate* pStaticObj;
	GTexture* blockGate;
public:
	void Init();
	void Draw();
	static BlockGate* GetStaticObj();
	BlockGate();
	~BlockGate();
};

