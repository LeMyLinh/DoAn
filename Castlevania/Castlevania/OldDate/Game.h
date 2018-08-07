#ifndef _GAME_H_
#define _GAME_H_
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


class CGame
{
protected:
	int ncmdShow;
	//GTexture* texture;
	GTexture* backGround;
	GSprite* Sprite;
	GSprite* test;
	Player* player;
	GCamera* camera;
	Map* map;
	Simon* simon;
	ObjManager* objManager;
	BlackBoard* blackBoard;

	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
	bool InitWindow(int nCmdShow);
	bool InitD3D9();
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	DWORD _DeltaTime;

public:
	CGame(int ncmdShow);
	void GameInit();
	void GameRun();
	void GameEnd();
	~CGame();
};
#endif // !_GAME_H_
