#include "GCamera.h"
#include "Global.h"
#include "Gate.h"

GCamera::GCamera(int width, int height, float _angle, D3DXVECTOR3 _scaleFactors, int x, int y,int layer)
{
	this->Width = width;
	this->Height = height;
	this->angle = _angle;
	this->scaleFactors = _scaleFactors;
	gate = -1;
	locaTime = 0;
	CloseGate = false;
	OpenGate = false;
	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, 0.0f, 1.0f);
	D3DXMatrixIdentity(&identityMatrix);
	save.x = x;
	save.y = y;
	save.layer = layer;
}

void GCamera::Update(int x,int y,int layer, bool &IsNextSatge, bool &IsAutoRun, int delta)
{
	//next state
	if (Islockcamera);
	else if (IsNextSatge == true)
	{	
		if (OpenGate)
		{
			if (indexGate > 1)
				indexGate = 1;
			if (indexGate == 1)
			{
				IsAutoRun = true;
				if (abs(x - save.xObj) >= 130)
				{
					IsAutoRun = false;
					OpenGate = false;
					CloseGate = true;
				}
			}
			CGate::GetStaticObj()->Update(save.xObj, save.yObj, indexGate);
			locaTime += delta;
			if (locaTime > 1000 / 4)
			{
				locaTime = 0;
				indexGate++;
			}			
		}
		else if (CloseGate)
		{					
			if (indexGate > -1 && indexGate < 2)
				CGate::GetStaticObj()->Update(save.xObj, save.yObj, indexGate);
			if (indexGate == -1)
			{			
				if (locaTime > 100 / 10)
				{
					locaTime = 0;
					if (save.turn == 1 && cameraX >= save.xObj + G_ScreenWidth/2 - 3)
					{
						IsNextSatge = false;
						CloseGate = false;
						G_Stage++;
						save.stage = G_Stage;
						gate = save.xObj;
						save.layer = layer;
						save.x = x;
						save.y = y;
					}

					else if (save.turn == -1 && cameraX <= save.xObj - G_ScreenWidth/2 + 3)
					{
						IsNextSatge = false;
						CloseGate = false;
						G_Stage++; 
						gate = save.xObj;
						save.stage = G_Stage;
						save.layer = layer;
						save.x = x;
						save.y = y;
					}
					else
						cameraX += save.turn * 3;
				}
			}
			locaTime += delta;
			if (locaTime > 1000 / 4)
			{
				locaTime = 0;
				if (indexGate >= 0)
					indexGate--;
			}		
		}
		else
		{
			locaTime += delta;
			if (locaTime > 100 / 10)
			{
				locaTime = 0;
				if (save.turn == 1 && cameraX >= save.xObj)
				{
					OpenGate = true;
					indexGate = 0;
				}

				else if (save.turn == -1 && cameraX <= save.xObj)
				{
					OpenGate = true;
					indexGate = 0;
				}
				else
					cameraX += save.turn * 3;
			}
		}
		


	}
	else
	{
		cameraX = x;

		switch (layer)
		{
		case 1:
			cameraY = STAGE1.bottom * 2 + 16 - G_ScreenHeight / 2;
			widthMap = STAGE1.right * 2;
			xMap = STAGE1.left * 2;
			break;
		case 2:
			cameraY = STAGE2.bottom * 2 + 16 - G_ScreenHeight / 2;
			widthMap = STAGE2.right * 2;
			xMap = STAGE2.left * 2;
			break;
		case 3:
			cameraY = STAGE3.bottom * 2 + 16 - G_ScreenHeight / 2;
			widthMap = STAGE3.right * 2;
			xMap = STAGE3.left * 2;
			break;
		case 4:
			cameraY = STAGE4.bottom * 2 + 16 - G_ScreenHeight / 2;
			widthMap = STAGE4.right * 2;
			xMap = STAGE4.left * 2;
			break;
		default:
			break;
		}

		//khoa camera
		if (gate != -1 && abs(x -gate)<400)
		{
			if (save.turn == 1 && cameraX > gate - G_ScreenWidth / 2)
				cameraX = gate - G_ScreenWidth / 2;
			if (save.turn == -1 && cameraX < gate + G_ScreenWidth / 2)
				cameraX = gate + G_ScreenWidth / 2;
		}
		if (cameraX > widthMap - G_ScreenWidth / 2)
			cameraX = widthMap - G_ScreenWidth / 2;
		if (cameraX < xMap + G_ScreenWidth / 2)
			cameraX = xMap + G_ScreenWidth / 2;
	}

	

	this->viewMatrix = D3DXMATRIX(
		scaleFactors.x * cos(angle), scaleFactors.x * sin(angle), 0, 0,
		-scaleFactors.y * sin(angle), scaleFactors.y * cos(angle), 0, 0,
		0, 0, scaleFactors.z, 0,
		-cameraX * scaleFactors.x * cos(angle) + cameraY * scaleFactors.y * sin(angle), -cameraX * scaleFactors.y * sin(angle) - cameraY * scaleFactors.y * cos(angle), 0, 1
		);
}

void GCamera::SetTransForm()
{
	G_lpDirect3DDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	G_lpDirect3DDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	G_lpDirect3DDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void GCamera::LockCamera()
{
}

RECT GCamera::GetRectCamera()
{
	RECT result;
	result.left = cameraX - Width / 2;
	result.right = cameraX + Width / 2;
	result.top = cameraY - Height / 2 + 90;
	result.bottom = cameraY + Height / 2;
	return result;
}

GCamera::~GCamera()
{
}
