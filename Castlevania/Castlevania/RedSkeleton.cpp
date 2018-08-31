#include "RedSkeleton.h"

RedSkeleton::RedSkeleton()
{
}

RedSkeleton::RedSkeleton(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	startIndex = 0;
	index = 0;
	endIndex = 1;
	vecY = 0;
	//gioi han
	turn = 1;
	vecX = 0;
	//Infomation
	HP = 1;
	Damage = 3;
	Point = 300;
	wait = 50;
	fid = index;
	localTime = 0;
	delayMove = 0;
	count = 0;
	numBone = 0;
	direct = turn;
	step = 2;
	IsFalling = true;
	allowFalling = false;
	IsJump = false;
	IsThrow = false;
}

void RedSkeleton::Update(Box RectCamera, Box simon, int Deltatime)
{
	if (abs(y - simon.y) > 280)
		return;
	Enemy::Update(RectCamera, simon, Deltatime);
	UpdateBone(RectCamera);

	if (delay < 20)
	{
		delay++;
		return;
	}
	UpdateSprite();

	//is jump
	if (abs(x - xold) <= bound && IsFalling && !IsJump)
	{
		IsJump = true;
		allowFalling = true;
		yold = y;
		vecY = 0;
	}

	//delay move
	if (numBone > 0)
	{
		if (wait < 10)
		{
			wait++;
		}
		else
		{
			Object t;
			t.SetObj(0, 0, x + 17, y + 15, 20, 27);
			t.temp = 270;
			t.SetVx(0);
			Bone.push_back(t);
			numBone--;
			wait = 0;
		}
	}
	else if (delayMove != 0)
		localTime += Deltatime;

	if (localTime >= delayMove || delayMove == 0)
	{
		//move
		localTime = 0;
		delayMove = 0;
		UpdateMove(RectCamera, simon, Deltatime);
	}
	else
	{
		if (step < 0 && numBone == 0)
		{
			srand(time(0));
			step = rand() % 2 + 1;
			count = 0;
			IsThrow = true;
			srand(time(0));
			int r1 = rand() % 100;
			if (r1 < 40)
				numBone = 1;
			else if (r1 < 70)
				numBone = 2;
			else if (r1 < 90)
				numBone = 3;
			else
				numBone = 4;
			wait = 0;
		}

		//stop
		if (x < simon.x)
			turn = 1;
		else
			turn = -1;
		direct = turn;
		//bound
		xold = x;
		srand(time(0));
		int r0 = rand() % 2;
		bound = 60 + r0 * 6;

	}

	IsFalling = true;
}

void RedSkeleton::UpdateSprite()
{
	fid += 0.06;
	index = (int)fid;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		fid = startIndex;
	}
}

void RedSkeleton::Draw()
{
	for (int i = 0; i < Bone.size(); i++)
	{
		EnemyRender::GetStaticObj()->DrawBone(Bone[i].GetX(), Bone[i].GetY(), Bone[i].index);
	}
	EnemyRender::GetStaticObj()->DrawSkeleton(x, y, index, direct);
}

void RedSkeleton::CollisionWithObj(Object * obj)
{
	Box t = GetBox();
	t.h += vecY;
	if (Collision::IsStandOnGround(t, obj->GetBox()) && !allowFalling)
	{
		y = obj->GetY() - 64;
		IsFalling = false;
		IsJump = false;
		allowFalling = false;
		yold = y;
		vecY = 0;
	}
	if (Collision::HitTheWall(GetBox(), obj->GetBox()))
	{
	}

}

void RedSkeleton::UpdateMove(Box RectCamera, Box simon, int deltatime)
{
	if (IsJump)
		vecX = 4 * turn;
	else
		vecX = 5.3 * turn;
	if (allowFalling == true)
	{
		if (y < (yold - 70))
		{
			allowFalling = false;
			IsFalling = true;
			vecY = 0;
		}
		else
		{
			if (vecY == 0)
				vecY = -10;
			else
				vecY *= 0.9;
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

	//update X
	if (abs(x - simon.x) <= 90 && !IsJump)
		turn = -direct;

	if (abs(x - xold) >= bound && !IsJump)
	{
		delayMove = 120;
		step--;
		vecX = 0;
	}

	//
	x += vecX;
	y += vecY;
}

void RedSkeleton::UpdateBone(Box camera)
{
	double pi = acos(-1);
	for (int i = 0; i < Bone.size(); i++)
	{
		Bone[i].SetVx(Bone[i].GetBox().vx + 0.1);
		Bone[i].index = (int)Bone[i].GetBox().vx;
		if (Bone[i].index > 1 || Bone[i].index < 0)
		{
			index = 0;
			Bone[i].SetVx(0);
		}
		if (Bone[i].temp <= 445)
		{
			Bone[i].temp += 4;
			Bone[i].SetVy(sinf((float)Bone[i].temp * pi / 180) * 10);
		}
		else
		{
			Bone[i].SetVy((Bone[i].GetBox().vy + 2));
		}

		Bone[i].SetY(Bone[i].GetY() + (Bone[i].GetBox().vy));
		Bone[i].SetX(Bone[i].GetX() + 2.5 * direct);
		if (!Collision::AABBCheck(Bone[i].GetBox(), camera))
			Bone.erase(Bone.begin() + i);
	}
}

void RedSkeleton::checkFight(Box vk, int lv)
{
	Enemy::checkFight(vk, lv);
	for (int i = 0; i < Bone.size(); i++)
	{
		if (Collision::AABBCheck(vk, Bone[i].GetBox()))
		{
			Object* obj = new Object();
			obj->SetObj(-1, -1, Bone[i].GetX(), Bone[i].GetY(), 20, 27);
			Effect::GetStaticObj()->Add(obj);
			Bone.erase(Bone.begin() + i);
		}
	}
}

bool RedSkeleton::CheckCollision(Box simon)
{
	if (Enemy::CheckCollision(simon))
		return true;
	for (int i = 0; i < Bone.size(); i++)
	{
		if (Collision::AABBCheck(simon, Bone[i].GetBox()))
		{
			return true;
		}
	}
	return false;
}



RedSkeleton::~RedSkeleton()
{
}
