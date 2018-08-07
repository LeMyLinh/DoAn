#include "BossLv2.h"
#include "EnemyRender.h"
#include "Global.h"
#include "Item.h"


BossLV2::BossLV2()
{
}

BossLV2::BossLV2(int _id, int _type, int _x, int _y, int _Width, int _Height) :Enemy(_id, _type, _x, _y, _Width, _Height)
{
	//Infomation
	HP = 16;
	Damege = 2;
	Point = 3000;
	IsFight = false;
	localTime = 0;
	maxTime = 0;
	localTime = 0;
	startIndex = 0;
	index = 0;
	endIndex = 3;
	tid = startIndex;
	delayMove = 0;
	IsSkill = false;
	bound = 100;
	move = false;
	vecX = 0;
	vecY = 0;
	snake.SetX(x);
	snake.IsDie = true;
	snake.temp = 0;
	vt = 1;
	xold = x;
	yold = y;
	spritBall.SetObj(0, 0, x + 28, y, 28, 32);
	spritBall.IsDie = true;
}

void BossLV2::Update(Box RectCamera, Box simon, int Deltatime)
{
	G_bossHP = HP;
	if (HP <= 0)
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
				NextLevel=true;
			}
		}
		return;
		
	}


	//Update Snake
	if (snake.IsDie == false)
	{
		snake.SetVy(snake.GetBox().vy*vt);
		snake.Update();
		if (!Collision::AABBCheck(snake.GetBox(), RectCamera))
			snake.IsDie = true;
		EnemyRender::GetStaticObj()->Snake->Update(Deltatime);
	}
	if (delay < 20)
	{
		delay++;
		return;
	}	

	if (!IsFight)
	{	
		index = 4;
		if (Collision::AABBCheck(simon, GetBox()))
		{
			Islockcamera = true;
			delayMove = 4000;
		}
		if (delayMove != 0)
			localTime += Deltatime;
		if (localTime >= delayMove && delayMove != 0)
		{
			IsFight = true;
			localTime = 0;
			delayMove = 1000;
		}

	}
	else
	{
		UpdateSprite();
		
		//delay move
		localTime += Deltatime;
		if (localTime >= delayMove)
		{
			//move
			localTime = 0;
			delayMove = 0;
			UpdateMove(RectCamera,simon);				
			vecX += 0.1*turn;	
			
		}
		else
		{
			//stop
			if (x < simon.x)
				turn = 1;
			else
				turn = -1;
			srand(time(0));
			int r0 = rand() % 2 + 1;
			bound = 100 + (r0 - 1) * 230;
			vecX = 2 * turn;
			vecX = 0;
			vecY = 0;
			xold = x;
			yold = y;
			turnOld = turn;
			if (snake.IsDie && !(x + Width >= RectCamera.x + RectCamera.w - 130))
				IsSkill = true;
		}


		
		if (IsSkill)
			Skill(simon);
	
		
	}
	
}

void BossLV2::UpdateSprite()
{
	tid += 0.4;
	index = (int)tid;
	if (index > endIndex || index < startIndex)
	{
		index = startIndex;
		tid = startIndex;
	}
}

void BossLV2::Effect()
{
}

void BossLV2::checkFight(Box vk, int lv)
{
	Enemy::checkFight(vk, lv);
	if (IsFight)
	{
		vecX = turn;
		if (Collision::AABBCheck(vk, snake.GetBox()))
		{
			Object* obj = new Object();
			obj->SetObj(-1, -1, snake.GetX(), snake.GetY(), 32, 20);
			Effect::GetStaticObj()->Add(obj);
			snake.IsDie = true;
		}
	}
}

bool BossLV2::CheckCollision(Box simon)
{
	if (!IsFight)
		return false;
	if (Enemy::CheckCollision(simon))
		return true;
	if (snake.IsDie==false)
	{
		if (Collision::AABBCheck(simon, snake.GetBox()))
			return true;		
	}
	return false;
}

void BossLV2::Draw()
{
	if (HP <= 0)
	{
		Item::GetStaticObj()->spriritBall->Draw(spritBall.GetX(), spritBall.GetY());
		return;
	}
	if (!snake.IsDie)
		EnemyRender::GetStaticObj()->DrawSnake(snake.GetX(), snake.GetY(), 0, turn);

	EnemyRender::GetStaticObj()->DrawBossLv2(x, y, index);
}

void BossLV2::Skill(Box simon)
{
	snake.IsDie = false;
	snake.SetObj(0, 0, (turn == -1) ? x + Width : x , y + 32, 14, 12);
	snake.SetVx(4*turn);
	snake.SetVy(2);
	snake.temp = 0;
	vt = 1;
	IsSkill = false;
}

void BossLV2::CollisionWithObj(Object * obj)
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
	if (snake.IsDie || snake.temp==1)
		return;
	if (Collision::HitTheWall(snake.GetBox(), obj->GetBox()))
	{
		
		vt = 1.2;
		snake.SetVy(2);
		snake.SetVx(0);
		snake.temp = 1;
		return;
	}
	Box bs = snake.GetBox();
	bs.h = snake.GetBox().h + snake.GetBox().vy;
	if (Collision::IsStandOnGround(bs, obj->GetBox()))
	{
		snake.SetY(obj->GetY() - 20);
		snake.SetVy(0);
	}
}

void BossLV2::UpdateMove(Box RectCamera, Box simon)
{
	turnOld = turn;
	if (abs(x - xold) >= bound)
	{
		vecX = 0;
		delayMove = 900;
	}
	if ((x >= RectCamera.x + RectCamera.w - 70 && turn == 1) || (x <= RectCamera.x + 30 && turn == -1))
	{
		turn *= -1;
		bound -= abs(x - xold);
		xold = x;
		vecX = 2 * turn;
	}	
	if (turn == 1 && turnOld == turn)
	{
		if (x > simon.x + simon.w && Collision::AABBCheck(GetBox(),simon))
		{
			srand(time(0));
			int r1 = rand() % 2;
			turn *= (1 - 2 * r1);
			bound -= abs(x - xold);
			xold = x;
			vecX = 2 * turn;
		}
	}
	else
		if (turn ==-1 && x + Width < simon.x && turnOld == turn && Collision::AABBCheck(GetBox(), simon))
		{
			srand(time(0));
			int r1 = rand() % 2;
			turn *= (1 - 2 * r1);
			bound -= abs(x - xold);
			xold = x;
			vecX = 2 * turn;
		}




	//update Y
				
	if (yold + Width - 50 <= simon.y )
	{
		vecY = 2;
	}
	else if (yold + Width  >= simon.y + simon.h - 10)
	{
		vecY = -2;
	}

	if (y + Heigt/2 + 3 >= 354)
	{
		if (abs(x - xold) > 50)
			vecY = 0;
		else
		{
			vecY = -2;
			yold = y;
		}
	}
	if (y + Heigt / 2 - 50 <= simon.y)
	{
		if (abs(x - xold) > 50)
			vecY = 0;
		else
		{
			vecY = 2;
			yold = y;
		}
	}

	//
	x += vecX;
	y += vecY;
}



BossLV2::~BossLV2()
{
	
}
