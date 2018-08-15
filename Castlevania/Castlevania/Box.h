#pragma once
#include <d3d9.h>

class Box
{
public:
	
	// position of top-left corner
	float x, y;

	// dimensions
	float w, h;

	// velocity
	float vx, vy;

	Box();
	~Box();

	void Update(float _x, float _y, float _w, float _h, float _vx, float _vy);

	//flip Box (swap x,y)
	Box FlipBox();
	
	static Box ConvertRECT(RECT rec);
};

