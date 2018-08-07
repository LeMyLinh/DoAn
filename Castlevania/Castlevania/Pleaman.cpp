#include "Pleaman.h"
#include "EnemyRender.h"



Pleaman::Pleaman()
{
}

Pleaman::Pleaman(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	startIndex = 0;
	index = 0;
	endIndex = 1;
	vecY = 0;
	//gioi han
	turn = 1;
	delayMove = 0;
	localTime = 0;
	xold = x;
	yold = y;
	vecX = 0;
	//Infomation
	HP = 1;
	Damege = 3;
	Point = 500;
	fid = index;
	//
	IsFight = false;
	IsJump = false;
	IsFalling = false;
	allowFalling = false;
	timejump = 5;
}

void Pleaman::Update(Box RectCamera, Box simon, int Deltatime)
{
	Enemy::Update(RectCamera, simon, Deltatime);
	if (!Collision::AABBCheck(GetBox(), RectCamera))
		IsDie = true;
	UpdateSprite();
	if (delay < 20)
	{
		delay++;
		return;
	}
	if (Collision::AABBCheck(GetBoundBox(), simon) && !IsFight)
	{
		if (x < simon.x)
			turn = 1;
		else
			turn = -1;
		IsFight = true;
		HightJump = 90;
	}
	if (IsFight)
	{
		if (Collision::AABBCheck(GetBox(), simon))
		{
			delayMove = 1500;
			localTime = 0;
		}
		if (delayMove != 0)
			localTime += Deltatime;
		if (localTime > delayMove || delayMove == 0)
		{
			//move
			localTime = 0;
			delayMove = 0;
			if (!IsJump)
			{
				if (x < simon.x)
					turn = 1;
				else
					turn = -1;
			}
		}
		
		if (abs(x  - simon.x) < 90 && !IsJump)
		{
			HightJump = 90;
			IsJump = true;
			allowFalling = true;
			yold = y;
			vecY = 0;
		}

		UpdateMove(RectCamera, simon, Deltatime);	
		IsFalling = true;
	}


}

void Pleaman::UpdateSprite()
{
	fid += 0.13;
	index = (int)fid;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		fid = startIndex;
	}
}

void Pleaman::Draw()
{
	EnemyRender::GetStaticObj()->DrawPleaman(x, y, index, turn);

}

void Pleaman::CollisionWithObj(Object * obj)
{
	Box t = GetBox();
	if (vecY == 0)
		t.h += 3;
	else
		t.h += vecY;
	if (Collision::IsStandOnGround(t, obj->GetBox()))
	{			
		y = obj->GetY() - 35;
		/*if (timejump >= 10)
			timejump = 0;*/
		if (timejump < 5 && vecY != 0)
		{
			timejump++;
			IsFalling = false;
			IsJump = false;
			allowFalling = false;
		}
		else
		{		
			timejump = 0;
			HightJump = 17;
			yold = y;
			allowFalling = true;
			IsJump = true;
			vecY = 0;
		}		
	}
	if (Collision::HitTheWall(GetBox(), obj->GetBox()))
	{
		if (HightJump == 90)
			turn *= -1;
		/*yold = y;
		vecY = 0;
		
		IsJump = true;
		allowFalling = true;*/
	}
}

void Pleaman::UpdateMove(Box RectCamera, Box simon, int deltatime)
{
	if (IsJump)
	{
		if (HightJump == 17)
			vecX = 5 * turn;
		else
			vecX = 4 * turn;
	}		
	else
		vecX = 0;
	//vecX = 4 * turn;


	if (allowFalling == true)
	{
		if (y < (yold - HightJump))
		{
			allowFalling = false;
			IsFalling = true;
			vecY = 0;
		}
		else
		{
			if (HightJump == 17)
			{
				if (vecY == 0)
					vecY = -5;
				else
					vecY *= 0.73;
			}
			else
			{
				if (vecY == 0)
					vecY = -10;
				else
					vecY *= 0.9;
			}
		}
	}
	else
	{
		if (IsFalling == true)
		{
			if (vecY == 0)
				vecY = 3;
			vecY *= 1.15;
		}
		else
		{
			//vecX = 0;
			vecY = 0;
		}
			
	}
	

	/*if (IsJump)
	{
		vecY += 0.1*deltatime;
		y += vecY*deltatime;
	}*/

	//
	x += vecX;
	y += vecY;
}

Box Pleaman::GetBoundBox()
{
	Box r = this->GetBox();
	r.x = x - 150;
	r.w = 300;
	r.h = 200;
	return r;
}


Pleaman::~Pleaman()
{
}
