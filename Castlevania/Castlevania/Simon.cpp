#include "Simon.h"
#include "KeyBoard.h"
#include "GSprite.h"
#include "GTexture.h"
#include "Global.h"
#include "Font.h"
#include <stdio.h>
#include "Collision.h"
#include "Object.h"
#include "Effect.h"
#include "Item.h"
#include "Weapon.h"

using namespace std;

Simon::Simon(int _x, int _y, int _inlayer)
{
	state = STAND;
	turn = TURN_RIGHT; //turn left
	x = _x;
	y = _y;

	vecX = 0;
	vecY = 0;
	//
	IsFalling = true;
	IsOnTheStair = false;
	IsOntheGround = true;
	IsFight = false;
	Isfind_Down = false;
	IsJumping = false;
	IsSkill = false;
	IsCombo = false;
	//
	lvOfMorningStar = 2;
	inLayer = _inlayer;
	sitDelay = 10;
	delayDeath = 0;
	effectDelay = 20;
	coutIndex = 0;
	Isfind = false;
	IsContinousClimb = false;
	tempMin = 0;
	IsBeaten = false;
	timeLocal = 0;
	timeEffect = 0;
	IsInvincible = false;
	IsStop = false;
	IsNextStage = false;
	FlipStair = false;
	IsAutoRun = false;
	IsDie = false;
	b = false;
	yold = 0;
	IscolorEffect = false;
	UseWP5 = false;
	//
	HP = 16;
	localTime = 0;
}

void Simon::Turn(int Turn)
{
	this->turn = Turn;
	Sprite->SetFormat(D3DXVECTOR2( -turn, 1), 0, 1);
}

void Simon::SetStateFight()
{
}

void Simon::SetState()
{
	if (IsDie)
	{
		state = STAND;
		return;
	}		
	IsSkill = false;
	if (IsBeaten)
		return;
	if (oldState != state)
		oldState = state;

	if (IsOntheGround)
	{
		if (KeyBoard::GetKey()->IsKeyDown(DIK_RIGHT) && Sprite->GetIndex() < 10)
		{
			state = RUNING;
			Turn(TURN_RIGHT);			
		}
		else if (KeyBoard::GetKey()->IsKeyDown(DIK_LEFT) && Sprite->GetIndex() < 10)
		{
			state = RUNING;
			Turn(TURN_LEFT);
		}
		else if (KeyBoard::GetKey()->IsKeyDown(DIK_DOWN))
		{
			state = SITING;
		}				
		else
		{
			state = STAND;
		}
		//
		if (KeyBoard::GetKey()->IsKeyDown(DIK_UP))
		{
			IsSkill = true;
		}
		if (KeyBoard::GetKey()->IsKeyDown(DIK_Z))
		{
			if (IsFight == false)
			{
				IsFight = true;
				//combo
				if (IsSkill == true && IsFight == true && Weapon::GetStaticObj()->Ready() == true)
				{
					if (Weapon::GetStaticObj()->typeWP == 5)
					{   
						UseWP5 = true;
						IsFight = false;
					}
					else
						IsCombo = true;
				}
			}
		}
		if (KeyBoard::GetKey()->IsKeyDown(DIK_X))
		{
			if (IsJumping == false && IsFalling == false)
			{
				IsJumping = true;
				state = JUMPING;
				y_old = y;
			}
		}
	}
	if (IsOnTheStair == true)
	{
		if (KeyBoard::GetKey()->IsKeyDown(DIK_UP))
		{
			if (IsFalling == false || Sprite->GetIndex() >= 10)
			{
				coutIndex = 0;
				state = CLIMBING_UP;
				IsSkill = true;
				y_old = y;
			}				
		}
		else if (KeyBoard::GetKey()->IsKeyDown(DIK_DOWN))
		{
			if (IsFalling == false || Sprite->GetIndex() >= 10)
			{
				coutIndex = 0;
				state = CLIMBING_DOWN;
				y_old = y;
			}			
		}
		else
		{
			//Dang dung o cau thang
			if (Sprite->GetIndex() >= 10)
			{
				if (Sprite->GetIndex() == 13 || (Sprite->GetIndex() == 12 && coutIndex == 0))
					state = CLIMBING_UP;
				else if (Sprite->GetIndex() == 11 || (Sprite->GetIndex() == 10 && coutIndex == 0))
					state = CLIMBING_DOWN;
				else
				{
					vecY = 0;
					if (IsFalling == true && (Sprite->GetIndex()==10|| Sprite->GetIndex()==12))
					{
						Sprite->SetAnimation(Sprite->GetIndex(), Sprite->GetIndex());
					}
				}			
			}
		}
	}	
}

void Simon::climb(Object* x)
{
	//dung giua bac thang
	if (y + Sprite->_FrameHeight < x->GetY() + x->GetBox().h && y + Sprite->_FrameHeight > x->GetY() + x->GetBox().h / 2)
	{
		y = (x->GetY() + x->GetBox().h / 2) - Sprite->_FrameHeight;
		this->x = x->GetX() + x->GetBox().w - Sprite->_FrameWidth + 17;
	}
	//dung tren
	if (y + Sprite->_FrameHeight < x->GetY() + x->GetBox().h / 2  && y + Sprite->_FrameHeight > x->GetY())
	{
		y = x->GetY() - Sprite->_FrameHeight;	
		this->x = x->GetX() + x->GetBox().w*3/2 - Sprite->_FrameWidth + 17;
	}
}

void Simon::climbDown(Object * x)
{
	vecX = 0;
	vecY = 0;
	float dBot;
	float dMid;
	float dTop;

	// tinh khoang cach cua simon so voi cau thang
	dBot = y + Sprite->_FrameHeight - (x->GetY() + x->GetBox().h);
	dMid = y + Sprite->_FrameHeight - (x->GetY() + x->GetBox().h / 2);
	dTop = y + Sprite->_FrameHeight - x->GetY();
	float min = 0;
	if (dBot > 32)
		return;
	if (Sprite->GetIndex() == 12)
	{
		if (x->GetX() + x->GetBox().w / 2 - (this->x + Sprite->_FrameWidth - 17) > 0)
			return;
		//tim min		
		min = (dBot > 0) ? dBot : 100;
		if (dMid >= 0)
		{
			min = (abs(min) < abs(dMid)) ? min : dMid;
		}
		if (dTop >= 0)
		{
			min = (abs(min) < abs(dTop)) ? min : dTop;
		}

		if (abs(min) > 3 && x->GetType() != LEFTSTAIR)
		{
			this->x += 1.5;
			this->y -= 1.5;
			IsContinousClimb = true;
			tempMin = min - 1.5;
			return;
		}
		min -= 1;
	}

	if (Sprite->GetIndex() == 10)
	{
		if (dTop <= 0)
			return;
		if (dMid <= 0)
		{
			min = (dMid < dBot) ? dBot : dMid;
		}
		else
		{
			min = dBot;
		}
		if (min == 0)
		{
			if (y + Sprite->_FrameHeight <= x->GetY() + x->GetBox().h / 2 + 2 && y + Sprite->_FrameHeight >= x->GetY())
			{
				this->x = x->GetX() - 12;
			}
		}
		if (abs(min)>10)
			return;
		if (abs(min) > 3)
		{
			this->x += -1.5;
			this->y -= -1.5;
			IsContinousClimb = true;
			tempMin = min + 1.5;
			return;
		}
	}
	if (min == 0)
	{
		return;
	}

	y = y - min;
	if (x->GetType() == LEFTSTAIR)
		this->x -= min;
	else
		this->x += min;
}

void Simon::SetAnimation(State _state)
{
	if (IsFight == true)
	{
		// dung danh
		if (Sprite->GetIndex() == 8 && (state == RUNING || state == STAND))
		{
			IsFight = false;
			SetAnimation(_state);
		}
		else if (Sprite->GetIndex() == 18 && state == SITING)
		{
			IsFight = false;
			SetAnimation(_state);
		}
		else if (Sprite->GetIndex() == 24)
		{
			IsFight = false;
			Sprite->SelectIndex(12);
			vecY = 0;
			vecX = 0;
		}
		else if (Sprite->GetIndex() == 21 && Sprite->GetEndIndex()==20) 
		{
			IsFight = false;
			Sprite->SelectIndex(10);
			vecY = 0;
			vecX = 0;
		}	
		else
		{
			if ((state == STAND || state == RUNING ) &&(Sprite->GetIndex()<10))
				Sprite->SetAnimation(5, 7, ONE_TURN);
			else if(state == STAND && (Sprite->GetIndex() ==10 || Sprite->GetIndex()==11 ||
				(Sprite->GetIndex() >=18 && Sprite->GetIndex()<=20)))
				Sprite->SetAnimation(18, 20, ONE_TURN);
			else if (state == STAND && (Sprite->GetIndex() == 12 || Sprite->GetIndex() == 13 ||
				(Sprite->GetIndex() >= 21 && Sprite->GetIndex() <= 23)))
				Sprite->SetAnimation(21, 23, ONE_TURN);
			else if (state == SITING)
				Sprite->SetAnimation(15, 17, ONE_TURN);
			if (IsCombo == false)
				MoringStar->SetAnimation(0 + 3 * lvOfMorningStar, 2 + 3 * lvOfMorningStar);
			if (IsFalling == false)
				vecX = 0;
		}
	}
	else
	{
		switch (_state)
		{
		case STAND:
			if (!(IsOnTheStair == true && IsFalling == true))
				Sprite->SelectIndex(0);
			vecX = 0;
			break;
		case RUNING:
			Sprite->SetAnimation(0, 3);
			vecX = SPEED_SIMON * turn;
			break;
		case JUMPING:
			Sprite->SelectIndex(4);
			break;
		case SITING:
			Sprite->SelectIndex(4);
			vecX = 0;
			break;
		case CLIMBING_UP:
			Sprite->SetAnimation(12, 13);
			if (turn != TURN_RIGHT)
			{
				Turn(TURN_RIGHT);
			}

			vecX = 1.5;
			vecY = -1.5;

			break;
		case CLIMBING_DOWN:
			Sprite->SetAnimation(10, 11);
			if (turn != TURN_LEFT)
			{
				Turn(TURN_LEFT);
			}
			vecX = -2;
			vecY = 2;
			break;
		case FIGHTING:
			break;
		case SIT_FIGHTING:
			break;
		case UP_FIGHTING:
			Sprite->SetAnimation(21, 23);
			break;
		case DOWN_FIGHTING:
			break;
			Sprite->SetAnimation(18, 20);
		default:
			break;
		}
	}
	//
	//oldIndex = Sprite->GetIndex();
	if(Sprite->GetIndex() == 13 && IsOnTheStair)
		coutIndex++;	
	if (Sprite->GetIndex() == 11 && IsOnTheStair)
		coutIndex++;
}

void Simon::Update(std::vector<Object*> listObject, std::vector<int*> &listInfo, BlackBoard* blacBoard,vector<Enemy*> listEnemy, int detaltime, GCamera* camera, ObjManager* objManager)
{
	if (UseWP5 == true)
	{
		if (blacBoard->HeartValue >= 5)
		{
			objManager->Frozen = 0;
			blacBoard->HeartValue -= 5;
		}
		UseWP5 = false;
	}
	if (delayDeath != 0)
		localTime += detaltime;
	else
		localTime = 0;
	if (delayDeath != 0 && localTime >= delayDeath)
	{
		localTime = 0;
		localTime = 0;
		delayDeath = 0;
		IsDie = false;
		Islockcamera = false;
		if (inLayer == 2)
			x = camera->save.x + 20;
		x = camera->save.x;
		y = camera->save.y;
		vecY = 0;
		inLayer = camera->save.layer;
		IsBeaten = false;
		HP = 16;
		blacBoard->HeartValue = 5;
		state = STAND;
		lvOfMorningStar = 0;
		objManager->Reset();
		Weapon::GetStaticObj()->Reset();
		return;
	}
	objManager->Isclear = false;
	if (IsNextStage)
	{
		objManager->Isclear = true;
		if (IsAutoRun)
		{
			state = RUNING;
			SetAnimation(state);
			x += vecX;
			y += vecY;
		}
		else
			Sprite->SetAnimation(Sprite->GetIndex(), Sprite->GetIndex());
		return;
	}			
	SetState();
	if (IsContinousClimb == true)
	{
		if (abs(tempMin) > 3)
		{
			if (tempMin > 0)
			{
				this->x += 1.5;
				this->y -= 1.5;
				tempMin -= 1.5;
			}
			else
			{
				this->x += -1.5;
				this->y -= -1.5;
				tempMin -= -1.5;
			}		
		}
		else
		{
			this->x += tempMin;
			this->y -= tempMin;
			IsContinousClimb = false;
		}
		return;
	}
	if (Isfind == true)
	{
		TimDuong(tempobj);
		if (Isfind == true)
			return;
	}
	/*if (Isfind_Down == true)
	{
		TimDuongXuong(tempobj);
		if (Isfind_Down == true)
			return;
	}*/	
	if (sitDelay < 10)
	{
		state = SITING;
		sitDelay++;
	}
	if (effectDelay < 20)
	{
		effectDelay++;
		return;
	}
	if (IsInvincible)
	{
		timeLocal += detaltime;
		if (timeLocal >= 2000)
		{
			timeLocal = 0;
			IsInvincible = false;
		}
	}
	SetAnimation(state);
	PickUpItem(blacBoard, objManager);	
	//
	IsFalling = true;
	IsOnTheStair = false;
	FlipStair = false;
	IsStop = false;
	FightEnemy(listEnemy);
	//Xet va cham:
	float normalx, normaly;
	float colisionTime;
	debug = listObject.size();
	if (inLayer == 2)
		countWall = 0;
	else
		countWall = 2;
	bool fhidden = false;
	for (int i = 0; i < listObject.size(); i++)
	{
		if(listInfo[listObject[i]->GetID()][6] == 1)
			continue;
		//stair
		if (listObject[i]->GetType() == STAIR || listObject[i]->GetType() == LEFTSTAIR || listObject[i]->GetType() == STAIRUN)
		{
			if (Collision::AABBCheck(this->GetBox(), listObject[i]->GetBox()))
			{
				if (Sprite->GetIndex() < 10 &&
					(y + Sprite->_FrameHeight - (listObject[i]->GetY() + listObject[i]->GetBox().h) > 5))
					continue;
				IsOnTheStair = true;
				if ((listObject[i]->GetType() == LEFTSTAIR || listObject[i]->GetType() == STAIRUN) && y+Sprite->_FrameHeight<= listObject[i]->GetY() + listObject[i]->GetBox().h)
					FlipStair = true;
				//tim duong len cau thang
				if (state == CLIMBING_UP && IsFalling == false)
				{
					if (y + Sprite->_FrameHeight - (listObject[i]->GetY() + listObject[i]->GetBox().h) == 0)
					{
						if (listObject[i]->GetType() == LEFTSTAIR)
						{
							//cau thang trai.
							if(listObject[i]->GetX() + listObject[i]->GetBox().w / 2  != x + 12)
							{
								Isfind = true;
								tempobj.SetObj(listObject[i]->GetID(), listObject[i]->GetType(), listObject[i]->GetX(), listObject[i]->GetY(), listObject[i]->GetBox().w, listObject[i]->GetBox().h);
								Update(listObject, listInfo, blacBoard, listEnemy, detaltime, camera, objManager);
							}
						}
						else if(listObject[i]->GetX() + listObject[i]->GetBox().w / 2 != x + Sprite->_FrameWidth - 17)
						{
							Isfind = true;
							tempobj.SetObj(listObject[i]->GetID(), listObject[i]->GetType(), listObject[i]->GetX(), listObject[i]->GetY(), listObject[i]->GetBox().w, listObject[i]->GetBox().h);
							Update(listObject, listInfo, blacBoard, listEnemy, detaltime, camera, objManager);
						}						
					}
				}
				//xu ly xuong cau thang				
				if (IsFalling == false && y + Sprite->_FrameHeight == listObject[i]->GetY() && Sprite->GetIndex() < 10)
				{
					b = true;
					yold = y;
				}
				if (state == CLIMBING_DOWN && Sprite->GetIndex() == 10 && y-yold>10 && b)
				{
					//if (y + Sprite->_FrameHeight <= listObject[i]->GetY() + listObject[i]->GetBox().h / 2 + 5 && y + Sprite->_FrameHeight >= listObject[i]->GetY())
					//{
						if (listObject[i]->GetType() == LEFTSTAIR)
							this->x = listObject[i]->GetX() + listObject[i]->GetBox().w- Sprite->_FrameWidth+ 17;
						else
							this->x = listObject[i]->GetX() - 12;
						b = false;
					//}
				}
				debug2 = listObject[i]->GetID();
				if (state == STAND &&Sprite->GetIndex() >= 10 && IsFalling == true)
				{
					climbDown(listObject[i]);
					if (IsContinousClimb == true)
						return;
					if (oldState == CLIMBING_DOWN && Sprite->GetIndex() == 10)
					{						
						//climb(listObject[i]);
					}
				}
				// va cham map;
				switch (inLayer)
				{
				case 4:
					if (y + 35 <= STAGE4.top * 2 && state == CLIMBING_UP)
					{
						inLayer = 3;
						y = STAGE3.bottom * 2 - Sprite->_FrameHeight;
						IsOnTheStair = true;
						SetState();
						vecY = 0;
					}
					break;
				case 3:
					if (y + 35 <= STAGE3.top * 2 && state == CLIMBING_UP)
					{
						inLayer = 2;
						y = STAGE2.bottom * 2 - Sprite->_FrameHeight;
						IsOnTheStair = true;
						SetState();
						vecY = 0;
					}
					if (y + Sprite->_FrameHeight + 5 >= STAGE3.bottom * 2 && state == CLIMBING_DOWN)
					{
						inLayer = 4;
						y = STAGE4.top * 2 - Sprite->_FrameHeight + 32;
					}
					break;
					case 2:
						if (y + 35 <= STAGE2.top * 2 && state == CLIMBING_UP)
						{
							inLayer = 1;
							y = STAGE1.bottom * 2 - Sprite->_FrameHeight;

						}
						if (y + Sprite->_FrameHeight + 5 >= STAGE2.bottom * 2 && state == CLIMBING_DOWN)
						{
							inLayer = 3;
							y = STAGE3.top * 2 - Sprite->_FrameHeight + 32;
						}
						break;
					case 1:
						if (y + Sprite->_FrameHeight >= STAGE1.bottom * 2 && state == CLIMBING_DOWN)
						{
							inLayer = 2;
							y = STAGE2.top * 2 - Sprite->_FrameHeight + 32;
						}
						break;
				default:
					break;
				}
			}
		}
		//ground
		if (listObject[i]->GetType() == GROUND || listObject[i]->GetType() == TOPSTAIR || listObject[i]->GetType() == STAIRUN)
		{		
			if (FlipStair&&Sprite->GetIndex() >= 10)
				continue;
			if (listObject[i]->GetType() == TOPSTAIR && Sprite->GetIndex()>=10)
			{
				continue;
			}		
			
			if (Collision::IsStandOnGround(this->GetBox(), listObject[i]->GetBox()))
			{
				y = listObject[i]->GetY() - this->GetBox().h;
				IsFalling = false;		
				if (IsBeaten)
				{
					IsBeaten = false;
					state = SITING;
					sitDelay = 2;
					IsInvincible = true;
				}
			}
			else
			{
				if (vecY > 15)
				{
					state = SITING;
					sitDelay = 0;
				}
				colisionTime = Collision::SweptAABB(this->GetBox(), listObject[i]->GetBox(), normalx, normaly);
				if (colisionTime < 1.0f &&colisionTime>0.0f && normaly == -1)
				{						
					x += vecX*colisionTime;
					y += vecY*colisionTime;
					if (IsBeaten)
					{
						IsBeaten = false;
						state = SITING;
						sitDelay = 2;
						IsInvincible = true;
					}					
					if (y == listObject[i]->GetY() - this->GetBox().h)
						IsFalling = false;
				}			
			}	
			Box tBox = this->GetBox();
			tBox.y = y + 3;
			tBox.h = Sprite->_FrameHeight - 3;
			int check = Collision::HitTheWall(tBox, listObject[i]->GetBox());
			if (check != 0 && Sprite->GetIndex()< 10)
			{
				countWall++;
				if (countWall < 2 && IsJumping == true)
					continue;
				IsStop = true;
				vecX = 0;
			}
		}
		//gate
		if (listObject[i]->GetType() == DOOR)
		{		
			camera->gate = listObject[i]->GetX();
			if(x<listObject[i]->GetX())
			camera->save.turn = 1;
			else
				camera->save.turn = -1;
			Box tempBox;
			tempBox = listObject[i]->GetBox();
			tempBox.w = listObject[i]->GetBox().w - 23;
			if (Collision::HitTheWall(this->GetBox(), tempBox) != 0)
			{
				vecX = 0;
				if (IsFalling == false)
				{
					IsNextStage = true;
					camera->save.layer = inLayer;
					camera->save.xObj = listObject[i]->GetX();
					camera->save.yObj = listObject[i]->GetY();
				}				
			}			
		}
		//candle
		else if (listObject[i]->GetType() == SMALLHEART || listObject[i]->GetType() == LARGEHEART ||
			listObject[i]->GetType() == AXE)	
		{
			Fight(listObject[i], listInfo,fhidden);
		}
	}
	
	if (IsBeaten == false)
	{
		CollisonWithEnemy(listEnemy);
	}
	if (IsBeaten == true)
	{
		beaten();
	}
	//Jumping
	if (IsJumping == true)
	{
		if (y < (y_old - HIGHT_JUMP) || (IsBeaten && y < (y_old - 50)))
		{
			vecY = 0;
			IsFalling = true;
			IsJumping = false;
		}
		else
		{
			if (IsFight == false && !IsBeaten)
			{
				Sprite->SelectIndex(4);
			}
			if (vecY == 0)
				vecY = -10;
			else
			{
				vecY *= 0.860;
			}
		}
	}
	else
	{
		if(Sprite->GetIndex()<10)
		{
			//Falling
			if (IsFalling == true)
			{
				if (vecY <= 0)
					vecY = 3;
				vecY *= 1.15;
			}
			else
			{
				vecY = 0;			
			}
			if (IsFalling == true && IsJumping == false && IsFight == false&& !IsBeaten)
			{
				Sprite->SelectIndex(0);
			}
		}	
	}	
	ThrowSubweapon(blacBoard);
	if (Islockcamera && x > 6000)
	{
		if (x < camera->GetRectCamera().left && vecX < 0)
			vecX = 0;
		if (x + Sprite->_FrameWidth>camera->GetRectCamera().right && vecX > 0)
			vecX = 0;
	}
	if (Islockcamera && x + 70 +vecX>=camera->GetRectCamera().right)
	{
		vecX = 0;
	}
	//
	if ((Sprite->GetIndex() == 10 || Sprite->GetIndex() == 11) && FlipStair)
	{
		Turn(TURN_RIGHT);
		vecX *= -1;
	}
	if ((Sprite->GetIndex() == 12 || Sprite->GetIndex() == 13) && FlipStair)
	{
		Turn(TURN_LEFT);
		vecX *= -1;
	}
	localTime += detaltime;
	CheckDie();
	//
	x += vecX;
	y += vecY;
	//if (oldIndex != Sprite->GetIndex())
		oldIndex = Sprite->GetIndex();
}

void Simon::Draw(int DeltaTime)
{
	if (IsDie && IsFalling==false&& state==STAND)
	{
		simonDeath->RenderTexture(x - 10 + simonDeath->Width / 2, y + simonDeath->Height / 2);
		return;
	}
	if (IsInvincible|| (effectDelay < 20))
	{
		EffectColor(DeltaTime);
	}
	else
		Sprite->SetColor();
	Sprite->SetTimeAni(1000 / 30);
	if (state == CLIMBING_UP || state == CLIMBING_DOWN)
	{
		Sprite->SetTimeAni(1000 / 18);
	}	
	Sprite->Draw(x + Sprite->_FrameWidth / 2, y + Sprite->_FrameHeight / 2);
	

	//Roi
	if (IsFight == true && Sprite->GetIndex()!=8 && IsCombo==false)
	{		
		MoringStar->SetFormat(D3DXVECTOR2(-turn, 1), 0, 1);
		MoringStar->SelectOrderIndex(Sprite->GetOrderIndex());
		MoringStar->SetTimeAni(1000 / 30);
		MoringStar->Draw(x + 28 * turn + Sprite->_FrameWidth / 2, y + Sprite->_FrameHeight / 2);
		MoringStar->Update(DeltaTime);
	}		
	
	if (effectDelay < 20)
	{
		return;
	}		
	else
	{
		Sprite->SetColor();
	}
	
	Sprite->Update(DeltaTime);
	debug4 = Sprite->GetIndex();
	char str[100];
}

void Simon::LoadResource(LPCWSTR resourceFile, int cols, int rows, int detalTime)
{
	BaseObject::LoadResource(resourceFile,cols,rows,detalTime);
	GTexture* t = new GTexture();
	t->loadTextTureFromFile(L"Resources/morningstar.png", D3DCOLOR_XRGB(255, 0, 255));
	MoringStar = new GSprite(t, 3, 3, 0);
	simonDeath = new GTexture();
	simonDeath->loadTextTureFromFile(L"Resources/simondeath.png", D3DCOLOR_XRGB(255, 0, 255));
}

//get Box
Box Simon::GetBox()
{	
	Box Result;
	Result.x = x + 12;
	Result.y = y;
	Result.w = Sprite->_FrameWidth - 29;
	if (state == SITING)
		Result.h = Sprite->_FrameHeight - 20;
	else
		Result.h = Sprite->_FrameHeight;
	Result.vx = turn;
	Result.vy = vecY;

	return Result;
}

int Simon::GetLayerMap()
{
	return inLayer;
}

void Simon::TimDuong(Object o)
{
	if (o.GetType() == LEFTSTAIR)
	{
		if (o.GetX() + o.GetBox().w / 2 < x + 12)
		{
			Turn(TURN_LEFT);
			state = RUNING;
			SetAnimation(state);
			x -= SPEED_SIMON;
			if (o.GetX() + o.GetBox().w / 2 >= x + 12)
			{
				x = o.GetX() + o.GetBox().w / 2 - 12;
				Isfind = false;
				state = CLIMBING_UP;
			}
		}
		if (o.GetX() + o.GetBox().w / 2 > x + 12)
		{
			y;
			Turn(TURN_RIGHT);
			state = RUNING;
			SetAnimation(state);
			x += SPEED_SIMON;
			//y += vecY;
			if (o.GetX() + o.GetBox().w / 2 <= x + 12)
			{
				x = o.GetX() + o.GetBox().w / 2 - 12;
				Isfind = false;
				state = CLIMBING_UP;
			}
		}
		return;
	}
	if (o.GetX() + o.GetBox().w / 2 < x + Sprite->_FrameWidth - 17)
	{
		Turn(TURN_LEFT);
		state = RUNING;
		SetAnimation(state);
		x -= SPEED_SIMON;
		//y += vecY;
		if (o.GetX() + o.GetBox().w / 2 >= x + Sprite->_FrameWidth - 17)
		{
			x = o.GetX() + o.GetBox().w / 2 - Sprite->_FrameWidth + 17;
			Isfind = false;
			state = CLIMBING_UP;
		}		
	}
	if(o.GetX() + o.GetBox().w / 2 > x + Sprite->_FrameWidth - 17)
	{
		Turn(TURN_RIGHT);
		state = RUNING;
		SetAnimation(state);
		x += SPEED_SIMON;
		//y += vecY;
		if (o.GetX() + o.GetBox().w / 2 <= x + Sprite->_FrameWidth - 17)
		{
			x = o.GetX() + o.GetBox().w / 2 - Sprite->_FrameWidth + 17;
			Isfind = false;
			state = CLIMBING_UP;
		}
	}
}

void Simon::TimDuongXuong(Object * o)
{
}

void Simon::PickUpItem(BlackBoard* blacBoard, ObjManager* objManager)
{
	for (int i = 0; i < Item::GetStaticObj()->GetListItem().size(); i++)
	{
		if (Collision::AABBCheck(this->GetBox(), Item::GetStaticObj()->GetListItem()[i].GetBox()))
		{
			//xu ly
			blacBoard->PickUpItem(Item::GetStaticObj()->GetListItem()[i].GetType());
			if (Item::GetStaticObj()->GetListItem()[i].GetType() == FIREBOMB)
			{
				objManager->Delete();
			}
			
			Weapon::GetStaticObj()->CheckWeaponInItem(Item::GetStaticObj()->GetListItem()[i]);
			//delete
			Item::GetStaticObj()->RemoveAt(i);
		}
	}
}

void Simon::CollisonWithEnemy(std::vector<Enemy*> listEnemy)
{
	if (IsDie)
		return;
	for (int i = 0; i < listEnemy.size(); i++)
	{		
		//va cham voi enemy
		if (listEnemy[i]->CheckCollision(this->GetBox()))
		{
			if (IsInvincible)
				return;
			if (listEnemy[i]->IsDie)
				continue;											
			//xu ly simon
			if (Sprite->GetIndex() >= 10)
			{
				HP -= listEnemy[i]->Damege;
				IsInvincible = true;
				return;
			}
			IsBeaten = true;
			HP -= listEnemy[i]->Damege;
			y_old = y;
			IsJumping = true;
			vecY = 0;
			if (vecX != 0)
			{
				if (vecX > 0)
				{
					Turn(TURN_LEFT);
				}
				else
				{
					Turn(TURN_RIGHT);
				}
			}
			else
			{
				if (listEnemy[i]->GetBox().vx>0)
				{
					Turn(TURN_RIGHT);
				}
				else
				{
					Turn(TURN_LEFT);
				}
			}
			vecX = 4 * (turn);

			//xu ly enemy
			if (listEnemy[i]->GetType() == MEDUSAHEAD)
			{
				Object* obj = new Object();
				obj->SetObj(0, 0, listEnemy[i]->GetX(), listEnemy[i]->GetY(), listEnemy[i]->Width, listEnemy[i]->Heigt);
				Effect::GetStaticObj()->Add(obj);
				listEnemy[i]->IsDie = true;
			}
					
			break;
						
		}
	}
}

void Simon::beaten()
{
	Sprite->SetAnimation(8, 8);	
	if (IsStop == false)
		vecX = 4 * turn;
	else
	{
		vecX = 0;
	}
	
}

void Simon::ThrowSubweapon(BlackBoard* blacBoard)
{
	if (IsFight == false)
		IsCombo = false;
	if (Sprite->GetIndex() == 7 || Sprite->GetIndex() == 17 || Sprite->GetIndex() == 20 || Sprite->GetIndex() == 23 )
	{
		if (IsCombo == false || Sprite->GetIndex()==oldIndex)
			return;
		Weapon::GetStaticObj()->Fight((turn == TURN_LEFT) ? x : x + Sprite->_FrameWidth - 10, y + 8, turn,blacBoard);
		IsSkill = false;
	}
}

void Simon::Fight(Object* o,std::vector<int*> &listInf,bool& fhidden)
{
	//kiem tra danh
	if (Sprite->GetIndex() == 7 || Sprite->GetIndex() == 17 || Sprite->GetIndex() == 20 || Sprite->GetIndex() == 23)
	{		
		if (lvOfMorningStar < 2)
			MorningStarBox.Update((turn == TURN_LEFT)? x - 40 : x+ Sprite->_FrameWidth - 10, y + 27 - 20 / 2, 50, 23, vecX, vecY);
		else
		{
			MorningStarBox.Update((turn == TURN_LEFT) ? x - 60 : x + Sprite->_FrameWidth - 10, y + 27 - 20 / 2, 80, 20, vecX, vecY);
		}

		if ((Collision::AABBCheck(MorningStarBox, o->GetBox()) && IsCombo == false)
			|| Weapon::GetStaticObj()->Check(o) == true)
		{			
			int* t = new int[7];
			Effect::GetStaticObj()->Add(o);
			Item::GetStaticObj()->Add(o,lvOfMorningStar);
			//o->IsDie = true;
			for (int i = 0; i < listInf.size(); i++)
			{
				t = listInf[i];
				if (t[0] == o->GetID())
				{
					delete listInf[o->GetID()];
					listInf.erase(listInf.begin() + o->GetID());
					return;
				}
			}			
			
		}		
	}
	//subWeapon
	if (Weapon::GetStaticObj()->Check(o) == true)
	{
		int* t = new int[7];
		Effect::GetStaticObj()->Add(o);
		Item::GetStaticObj()->Add(o,lvOfMorningStar);
		for (int i = 0; i < listInf.size(); i++)
		{
			t = listInf[i];
			if (t[0] == o->GetID())
			{
				delete listInf[o->GetID()];
				listInf.erase(listInf.begin() + o->GetID());
				return;
			}
		}
	}
}

void Simon::FightEnemy(vector<Enemy*> listEnemy)
{
	if (Sprite->GetIndex() == 7 || Sprite->GetIndex() == 17 || Sprite->GetIndex() == 20 || Sprite->GetIndex() == 23)
	{
		int lv = lvOfMorningStar;
		if (lvOfMorningStar < 2)
			MorningStarBox.Update((turn == TURN_LEFT) ? x - 40 : x + Sprite->_FrameWidth - 10, y + 27 - 20 / 2, 50, 23, vecX, vecY);
		else
		{
			lv = 1;
			MorningStarBox.Update((turn == TURN_LEFT) ? x - 60 : x + Sprite->_FrameWidth - 10, y + 27 - 20 / 2, 80, 20, vecX, vecY);
		}
		if (oldIndex == Sprite->GetIndex())
			return;
		for (int i = 0; i < listEnemy.size(); i++)
		{
			listEnemy[i]->checkFight(MorningStarBox, lv + 1);
		}
	}
	//subWeapon
	for (int i = 0; i < listEnemy.size(); i++)
	{
		if (listEnemy[i]->IsDie)
			continue;
		if(Weapon::GetStaticObj()->Check(listEnemy[i]))
		{ 
			listEnemy[i]->Beaten(Weapon::GetStaticObj()->damge);
		}
	}
	
}

void Simon::EffectColor(int delta)
{
	timeEffect += delta;
	/*if (timeEffect > 1000 / 60)
	{
		timeEffect = 0;*/
		IscolorEffect = !IscolorEffect;
	//}
	if (IscolorEffect)
	{
		Sprite->SetColor(0xAAAAAAAA);
	}
	else
	{
		Sprite->SetColor();
	}
}

void Simon::CheckDie()
{
	if (IsDie)
		return;
	if (HP <= 0)
	{
		IsDie = true;
		delayDeath = 3000;
		return;
	}
	if (Sprite->GetIndex() >= 10/* && IsFalling ==false*/)
		return;
	Box c;
	switch (inLayer)
	{
	case 1:
		c = Box::ConvertRECT(STAGE1);
		c.x *= 2;
		c.y *= 2;
		c.w *= 2;
		c.h *= 2;	
		break;
	case 2:
		c = Box::ConvertRECT(STAGE2);
		c.x *= 2;
		c.y *= 2;
		c.w *= 2;
		c.h *= 2;
		break;
	case 3:
		c = Box::ConvertRECT(STAGE3);
		c.x *= 2;
		c.y *= 2;
		c.w *= 2;
		c.h *= 2;		
		break;
	case 4:
		c = Box::ConvertRECT(STAGE4);
		c.x *= 2;
		c.y *= 2;
		c.w *= 2;
		c.h *= 2;
		break;
	default:
		break;
	}
	c.y -= 32;
	c.h += 32;
	if (!Collision::AABBCheck(this->GetBox(), c))
	{
		delayDeath = 3000;
		IsDie = true;
	}		
}

int Simon::GetHP()
{
	if (HP > 0)
		return HP;
	return 0;
}

Simon::~Simon()
{
}
