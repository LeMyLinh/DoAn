#include "Player.h"
#include "GSprite.h"
#include "Global.h"
#include <Windows.h>



Player::Player(GSprite *sprite):_sprite(sprite)
{
	x = _sprite->_FrameWidth / 2;
	y = GROUND_Y;
	turn = TURN_RIGHT;
	VecX = 0;
	vecY = 0;
	Santo = 0;
	state = STANDs;
}

void Player::Update()
{
	/*x += VecX;
	if (vecY < 0)
	{
		if (y <= GROUND_Y || y >= GROUND_Y-100)
		{
			if (y > GROUND_Y - 60 && y < GROUND_Y)
				_sprite->SelectIndex(8);
			else
			{
				Santo += 21*turn;
				_sprite->SetFormat(D3DXVECTOR2(turn, 1), Santo, 1);
				if (y > GROUND_Y - 80 && y < GROUND_Y - 60)
					_sprite->SelectIndex(9);
				else
					_sprite->SelectIndex(11);
			}
			y += vecY;
		}
		if (y < GROUND_Y - 90)
		{			
			vecY = -vecY;

		}
		if (Santo > 360 ||Santo <-360)
			Santo = 0;
	}
	if (vecY > 0)
	{
		if (y > GROUND_Y - 100 && y < GROUND_Y - 50)
			_sprite->SelectIndex(11);
		else
			_sprite->SelectIndex(10);
		Santo += 23*turn;
		_sprite->SetFormat(D3DXVECTOR2(turn, 1), Santo, 1);
		if (y >= GROUND_Y)
		{
			vecY = 0;
			Santo = 0;
			y = GROUND_Y;
			_sprite->SetFormat(D3DXVECTOR2(turn, 1), Santo, 1);

		}
		y += vecY;
		
	}*/
}

void Player::Turn(int turn)
{
	this->turn = turn;
	_sprite->SetFormat(D3DXVECTOR2(turn, 1), 0, 1);
}


void Player::Draw()
{
	/*_sprite->Draw(x, y);
	_sprite->Next();*/
}

void Player::SetState(States _state)
{
	state = _state;
	if (state == STANDs)
	{
		if (y == GROUND_Y)
			_sprite->SelectIndex(0);
		VecX = 0;
	}
	if (state == RUN)
	{
		_sprite->SetAnimation(1, 7);
		VecX = 6*turn;
	}
	if (state == SIT)
	{
		_sprite->SelectIndex(11);
		VecX = 0;
	}
	if (state == JUMP)
	{
		if (y == GROUND_Y)
		{
			_sprite->SetAnimation(8, 10);
			vecY = -10;
		}
	}
}


int Player::GetY()
{
	return y;
}

int Player::GetX()
{
	return x;
}

Player::~Player()
{
}
