#ifndef _GAME_H_
#define _GAME_H_
#include <d3d9.h>
#include <dinput.h>
#include "Global.h"

class CGame
{
protected:
	int ncmdShow;
	//GTexture* texture;
	/*GTexture* backGround;
	GSprite* Sprite;
	GSprite* test;*/
	//Player* player;
	//GCamera* camera;
	//Map* map;
	//Simon* simon;
	//ObjManager* objManager;
	//BlackBoard* blackBoard;

	static LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
	bool InitWindow(int nCmdShow);
	bool InitD3D9();
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	DWORD _DeltaTime;

	//keyboard
	void InitKeyboard();

	void ProcessKeyBoard();

	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void UpdateGame(LPDIRECT3DDEVICE9 d3ddv, int Delta);

	virtual void OnKeyUp(int KeyCode);
	virtual void OnKeyDown(int KeyCode);

	int IsKeyDown(int KeyCode);

	BYTE  _KeyStates[256]; // DirectInput keyboard state buffer 

	DIDEVICEOBJECTDATA _KeyEvents[GL_KEY_BUFFER_SIZE]; // Buffered keyboard data

public:
	CGame(int ncmdShow);
	void GameInit();
	void GameRun();
	void GameEnd();
	~CGame();
};
#endif
