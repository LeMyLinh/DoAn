#include "Gate.h"
#include "Constant.h"

CGate* CGate::pStaticObj = 0;

CGate::CGate()
{
}

void CGate::Init()
{
	BaseObject::LoadResource(GATE_IMAGE, COL_OF_GATE, ROW_OF_GATE, TIME_ANIM_GATE);
	IsDraw = false;
}

CGate * CGate::GetStaticObj()
{
	if (pStaticObj == 0)
		pStaticObj = new CGate();

	return pStaticObj;
}

void CGate::Update(int _x, int _y, int _index)
{
	x = _x;
	y = _y;
	index = _index;
	IsDraw = true;
}


void CGate::Draw()
{
	if (IsDraw)
	{
		Sprite->SelectIndex(index);
		Sprite->Draw(x - Sprite->_FrameWidth / 2 + 40, y + Sprite->_FrameHeight/2);
		IsDraw = false;
	}
	
}

CGate::~CGate()
{
}
