#include "Panther.h"

Panther::Panther()
{
}

Panther::~Panther()
{
}

Panther::Panther(int _id, int _type, int _x, int _y, int _Width, int _Height) :
	Enemy(_id, _type, _x, _y, _Width, _Height)
{
	hasJump = false;
	startIndex = 0;
	index = 0;
	endIndex = 3;
	vecY = 0;
	virtualVecX = 5;
	turn = -1;
	vecX = turn * 1.5;

	//Infomation
	HP = 1;
	Damage = 2;
	Point = 200;
	temp = index;

	isSleeping = true;
	hasJump = false;
}
void Panther::Update(Box RectCamera, Box simon, int Deltatime)
{
	delay += Deltatime;
	UpdateSprite();
	if (delay < 6)
		return;
	Enemy::Update(RectCamera, simon, Deltatime);
	if (!IsFight)
	{
		if (x < simon.x)
		{
			turn = 1;
		}
		else
			turn = -1;
		if (Collision::AABBCheck(GetBoundBox(), simon))
		{
			IsFight = true;
			x += turn * virtualVecX;

		}




	}
	else
	{
		if (x < simon.x - 50)
		{
			turn = 1;
		}
		else if (x > simon.x + 50)
			turn = -1;

		//hàm xử lý chạy nhảy của con panther
		if (x > simon.x + 200)
		{
			vecX -= turn;
			vecY = 0;
		}
		else if (x < simon.x - 100)
		{

			vecY = 0;
			vecX += turn;
		}
		if (abs(x - simon.x) < 100 && !hasJump)
		{
			if (delay < 200)
			{
				vecX += 2 * turn;
				vecY -= 1;
			}
			else if (delay < 600)
			{

				vecX += turn;
				vecY += 1.5;
			}
			else
			{

				delay = 0;
			}
		}
	}

	x += vecX;
	y += vecY;


}
void Panther::UpdateSprite()
{
	fid += 0.13;
	index = (int)fid;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		fid = startIndex;
	}
}
void Panther::Draw()
{
	EnemyRender::GetStaticObj()->DrawPanther(x, y, index, turn);

}
void Panther::CollisionWithObj(Object* obj)
{
	Box t = GetBox();
	t.h += vecY;
	if (Collision::IsStandOnGround(t, obj->GetBox()))
	{
		y = obj->GetY() - 32;
		vecY = 0;
	}
	if (Collision::HitTheWall(GetBox(), obj->GetBox()))
	{
	}
}
bool Panther::CheckCollision(Box simon)
{
	vecX = turn;
	if (Enemy::CheckCollision(simon))
		return true;
	else if (isFight)
	{
		//
	}
	return false;
}
void Panther::UpdateMove(Box RectCamera, Box simon, int deltatime)
{

}
Box Panther::GetBoundBox()
{
	Box r = this->GetBox();
	r.x = x - 100;
	r.w = 200;
	r.h = 100;
	return r;
}

