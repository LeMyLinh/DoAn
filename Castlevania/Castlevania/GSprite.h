#ifndef _GSPRITE_H_
#define _GSPRITE_H_

#include <d3d9.h>
#include <d3dx9.h>

#include "GTexture.h"

enum MODE
{
	REPEAT,
	ONE_TURN,
	CONTINUOUS
};

class GSprite
{
private:
	GTexture* _texture;

	int _Cols;		//số cột frame
	int _Rows;		//số hàng frame
	int _Count;		//tổng số frame

	RECT _rect; //size cua frame;

	int _index; //frame hien tai
	int _timeAni; // thoi gian chuyen frame
	int _timeLocal; //bien dem thoi gian
	int _start; //chay tu frame;
	int _end; //chay den frame;
	MODE mode; //che do

public:
	int _FrameWidth;		//width of 1 frame
	int _FrameHeight;	//height of 1 frame
	GSprite(GTexture* texture,int cols,int rows,int timeAnimation);
	GSprite(GTexture* texture, int cols, int rows, int timeAnimation, int start, int end);
	~GSprite();

	//sang frame tiếp theo
	void Next();

	//trở về frame đầu tiên
	void Reset();

	//chọn 1 frame nào đó
	void SelectIndex(int index);
	void SelectOrderIndex(int order);

	//định dạng frame (flipX, flipY, zoom, quay).
	void SetFormat(D3DXVECTOR2 scale,
		float angle,
		float deep,
		D3DCOLOR color = 0xffffffff);
	void SetDefault();
	//update animation
	void Update(int ellapseTime);
	void SetAnimation(int start,int end);
	void SetAnimation(int start, int end, MODE Mode);
	void SetTimeAni(int timeAni);
	void SetMode(MODE Mode);
	void SetColor(D3DCOLOR _color = 0xffffffff);
	// Render current sprite at location (X,Y) at the target surface
	void Draw(int x, int y);
	void Draw(int x, int y, int index);
	//get index
	int GetIndex();
	int GetOrderIndex();
	int GetEndIndex();
	RECT GetSizeFrame();
};

#endif // !_GSPRITE_H_



