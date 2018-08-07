#include "Bosslv3.h"
#include "Item.h"

float BosslV3::mau = 16;

BosslV3::BosslV3()
{
}

BosslV3::BosslV3(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	startIndex = 0;
	index = 0;
	endIndex = 5;
	vecY = 0;
	//gioi han
	turn = 1;
	vecX = 0;
	//Infomation
	HP = 16;
	Damege = 1;
	Point = 300;
	wait = 50;
	fid = index;
	localTime = 0;
	localTime1 = 0;
	delayMove = 0;
	numBone = 0;
	direct = turn;
	IsSleep = true;
	delayFight = 1;
	spritBall.SetObj(0, 0, 6900, 224, 28, 32);
	spritBall.IsDie = true;

}

void BosslV3::Update(Box RectCamera, Box simon, int Deltatime)
{
	G_bossHP = (int)mau;
	if (HP <= 0)
	{
		if (mau > 0)
			IsDie = true;
		else
		{
			x = -Width;
			localTime += Deltatime;
			if (localTime >= 1000)
			{
				spritBall.IsDie = false;
				spritBall.SetVy(2);
				spritBall.Update();
				Item::GetStaticObj()->spriritBall->Update(Deltatime);
				if (Collision::AABBCheck(simon, spritBall.GetBox()))
				{
					NextLevel = true;
				}
			}
			return;
		}
	}
	Updatethick(RectCamera);
	if (delay < 20)
	{		
		delay++;
		return;
	}
	UpdateSprite();
	if (simon.x >= 6921 && IsSleep)
	{
		IsSleep = false;
		Islockcamera = true;
		delayFight = 2000;
	}
	else if (delayFight != 1)
		localTime1 += Deltatime;
	if (localTime1 < delayFight)
	{
		return;
	}
	if (IsSleep)
		return;

	//delay move
	if (IsThrow)
	{
		startIndex = 3;
		endIndex = 5;
		if (wait < 20)
		{
			wait++;
		}
		else
		{
			Object t;
			t.SetObj(0, 0, x + 17, y + 22, 34, 20);
			t.temp = 0;
			t.SetVx(0);			
			Thick.push_back(t);
			IsThrow = false;
			wait = 0;
		}
	}
	else if (delayMove != 0)
		localTime += Deltatime;
	if (localTime >= delayMove || delayMove == 0)
	{
		startIndex = 0;
		endIndex = 2;
		//move
		localTime = 0;
		delayMove = 0;
		UpdateMove(RectCamera, simon, Deltatime);
	}
	else
	{
		if (step < 0)
		{
			srand(time(0));
			step = rand() % 2 + 1;
			IsThrow = true;
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
		bound = 40 + r0 * 6;

	}
}

void BosslV3::UpdateSprite()
{
	fid += 0.06;
	index = (int)fid;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		fid = startIndex;
	}
}

void BosslV3::Draw()
{
	if (HP <= 0 && mau ==0)
	{
		Item::GetStaticObj()->spriritBall->Draw(spritBall.GetX(), spritBall.GetY());
		return;
	}
	for (int i = 0; i < Thick.size(); i++)
	{
		EnemyRender::GetStaticObj()->DrawThick(Thick[i].GetX(), Thick[i].GetY(), Thick[i].index);
	}
	EnemyRender::GetStaticObj()->DrawBosslv3(x, y, index, turn);
}

void BosslV3::UpdateMove(Box RectCamera, Box simon, int deltatime)
{
	//update X
	if (abs(x - simon.x) <= 70)
		turn = -direct;

	if (abs(x - xold) >= bound || (x< RectCamera.x && vecX<0) || (x + Width>RectCamera.x + RectCamera.w && vecX>0))
	{
		delayMove = 180;
		step--;		
	}

	vecX = 3 * turn;
	//
	x += vecX;
	y += vecY;
}

void BosslV3::Updatethick(Box camera)
{
	double pi = acos(-1);
	for (int i = 0; i < Thick.size(); i++)
	{
		Thick[i].temp += 5;
		if (Thick[i].temp > 360)
			Thick[i].temp = 0;
		Thick[i].SetVy(sinf((float)Thick[i].temp * pi / 180) * 3);
		Thick[i].SetY(Thick[i].GetY() + (Thick[i].GetBox().vy));
		Thick[i].SetVx(4 * direct);
		Thick[i].SetX(Thick[i].GetX() + 5 * direct);
		if (!Collision::AABBCheck(Thick[i].GetBox(), camera))
			Thick.erase(Thick.begin() + i);
	}
}


void BosslV3::checkFight(Box vk, int lv)
{
	int t = HP;
	if (IsSleep)
		return;
	Enemy::checkFight(vk, lv);
	for (int i = 0; i < Thick.size(); i++)
	{
		if (Collision::AABBCheck(vk, Thick[i].GetBox()))
		{
			Object* obj = new Object();
			obj->SetObj(-1, -1, Thick[i].GetX(), Thick[i].GetY(), 34, 20);
			Effect::GetStaticObj()->Add(obj);
			Thick.erase(Thick.begin() + i);
		}
	}
	mau -= (t - HP) / 2;
}

bool BosslV3::CheckCollision(Box simon)
{
	if (IsSleep)
		return false;
	if (Enemy::CheckCollision(simon))
		return true;
	for (int i = 0; i < Thick.size(); i++)
	{
		if (Collision::AABBCheck(simon, Thick[i].GetBox()))
		{
			return true;
		}
	}
	return false;
}

void BosslV3::CollisionWithObj(Object * obj)
{
	if (!spritBall.IsDie)
	{
		Box bp = spritBall.GetBox();
		bp.h = spritBall.GetBox().h + spritBall.GetBox().vy;
		if (Collision::IsStandOnGround(bp, obj->GetBox()))
		{
			spritBall.SetY(obj->GetY() - 20);
			spritBall.SetVy(0);
		}
	}
}


BosslV3::~BosslV3()
{
}
