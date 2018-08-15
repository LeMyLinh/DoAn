#include "Box.h"

Box::Box()
{
}


Box::~Box()
{
}

void Box::Update(float _x, float _y, float _w, float _h, float _vx, float _vy)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	vx = _vx;
	vy = _vy;
}

Box Box::FlipBox()
{
	x = x + y;
	y = x - y;
	x = x - y;

	w = w + h;
	h = w - h;
	w = w - h;
	Box result;
	result.x = x;
	result.y = y;
	result.w = w;
	result.h = h;
	return result;
}

Box Box::ConvertRECT(RECT rec)
{
	Box b;
	b.x = rec.left;
	b.y = rec.top;
	b.w = rec.right - rec.left;
	b.h = rec.bottom - rec.top;
	return b;
}