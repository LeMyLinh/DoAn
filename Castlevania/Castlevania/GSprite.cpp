#include "GSprite.h"
#include "Global.h"
#include "GTexture.h"



GSprite::GSprite(GTexture * texture, int cols, int rows, int timeAnimation) :_texture(texture)
{
	this->_texture = texture;
	this->_Cols = cols;
	this->_Rows = rows;
	this->_timeAni = timeAnimation;

	this->_FrameHeight = this->_texture->Height / rows;
	this->_FrameWidth = this->_texture->Width / cols;
	this->_Count = rows * cols;
	this->_start = 0;
	this->_index = _start;
	this->_end = _Count - 1;
	this->_timeLocal = 0;

	this->_rect = { 0,0,_FrameWidth,_FrameHeight };

	mode = REPEAT;
}

GSprite::GSprite(GTexture * texture, int cols, int rows, int timeAnimation, int start, int end) :_texture(texture)
{
	this->_texture = texture;
	this->_Cols = cols;
	this->_Rows = rows;
	this->_timeAni = timeAnimation;

	this->_FrameHeight = this->_texture->Height / rows;
	this->_FrameWidth = this->_texture->Width / cols;
	this->_Count = rows * cols;
	this->_start = start;
	this->_index = _start;
	this->_end = end;
	this->_timeLocal = 0;

	this->_rect = { 0,0,_FrameWidth,_FrameHeight };
	mode = REPEAT;
}

GSprite::~GSprite()
{
	if (_texture != NULL) delete _texture;
}

void GSprite::Next()
{
	if (mode == REPEAT)
	{
		_index++;
		if (_index<_start || _index > _end)
		{
			_index = _start;
		}

	}
	else if (mode == ONE_TURN)
	{
		if (_index <= _end)
			_index++;

	}
}


void GSprite::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void GSprite::SelectIndex(int index)
{
	_index = index;
}

void GSprite::SelectOrderIndex(int order)
{
	_index = _start + order - 1;
}

void GSprite::SetFormat(D3DXVECTOR2 scale, float angle, float deep, D3DCOLOR color)
{
	_texture->SetFormat(scale, angle, deep, color);
}

void GSprite::SetDefault()
{
	_texture->SetDefaul();
}

void GSprite::Update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni)
	{
		_timeLocal = 0;
		this->Next();
	}
}

void GSprite::SetAnimation(int start, int end)
{
	/*if (start != _start || end != _end)
	{*/
	mode = REPEAT;
	_start = start;
	_end = end;
	if (_index<start || _index>end)
		_index = start;
	//}	
}

void GSprite::SetAnimation(int start, int end, MODE Mode)
{
	/*if (start != _start || end != _end)
	{*/
	_start = start;
	_end = end;
	mode = Mode;
	if (_index<start || _index>end)
		_index = start;
	//}
}



void GSprite::SetTimeAni(int timeAni)
{
	_timeAni = timeAni;
}

void GSprite::SetMode(MODE Mode)
{
	mode = Mode;
}

void GSprite::SetColor(D3DCOLOR _color)
{
	_texture->SetColor(_color);
}


void GSprite::Draw(int x, int y)
{
	_rect.top = ((int)_index / _Cols)*_FrameHeight;
	_rect.left = (_index % _Cols)*_FrameWidth;
	_rect.right = _rect.left + _FrameWidth;
	_rect.bottom = _rect.top + _FrameHeight;

	//cap nhat lai toa do
	_texture->RenderTexture(x, y, _rect);
}

void GSprite::Draw(int x, int y, int index)
{
	if (index == -1)
		return;
	this->SelectIndex(index);
	this->Draw(x, y);
}

int GSprite::GetIndex()
{
	return _index;
}

int GSprite::GetOrderIndex()
{
	return _index - _start + 1;
}

int GSprite::GetEndIndex()
{
	return _end;
}

RECT GSprite::GetSizeFrame()
{
	return this->_rect;
}
