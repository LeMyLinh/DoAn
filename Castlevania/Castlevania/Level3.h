#pragma once
#include "Scene.h"
#include <Windows.h>
#include <cstdlib> 
#include <ctime> 
#include <dinput.h>
#include "Scene.h"
#include <d3d9.h>
#include <dinput.h>
#include "Global.h"
#include "GTexture.h"
#include "GSprite.h"
#include "Player.h"
#include "GCamera.h"
#include "Map.h"
#include "Simon.h"
#include "ObjManager.h"
#include "BlackBoard.h"
#include "Global.h"

#include "KeyBoard.h"
#include "Font.h"
#include "Tile.h"
#include "BigCandel.h"
#include "SmallCandle.h"
#include "Stair.h"
#include "Effect.h"
#include "TopStair.h"
#include "EnemyRender.h"
#include "Item.h"
#include "Gate.h"
#include "Weapon.h"

class Level3: public Scene
{	
	GCamera* camera;
	Map* map;
	Simon* simon;
	ObjManager* objManager;
	BlackBoard* blackBoard;
public:
	Level3();
	virtual void RenderFrame(int Delta);
	virtual void ProcessInput_UP(int Delta);
	virtual void ProcessInput_DOWN(int Delta);
	virtual void ProcessInput_RIGHT(int Delta);
	virtual void ProcessInput_LEFT(int Delta);
	virtual void ProcessInput(int Delta);
	virtual void UpdateGame(int Delta);
	virtual void LoadResources();
	virtual void OnKeyDown(int KeyCode);
	~Level3();
};

