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
