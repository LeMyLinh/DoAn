#include "Game.h"
#include "Global.h"
#include "GTexture.h"
#include <Windows.h>
#include <cstdlib> 
#include <ctime> 
#include <dinput.h>
#include "KeyBoard.h"
#include "Font.h"
#include "Tile.h"
#include "BigCandel.h"
#include "SmallCandle.h"
#include "Stair.h"
#include "Effect.h"
#include "TopStair.h"
#include "EnemyRender.h"


CGame::CGame(int _ncmdShow)
{
	ncmdShow = _ncmdShow;
	//texture = new GTexture();
	backGround = new GTexture();
	map = new Map();
	simon = new Simon();
	objManager = new ObjManager();
	blackBoard = new BlackBoard();
}

LRESULT CALLBACK CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool CGame::InitWindow(int nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = G_hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GAME_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	int windowStyle;
	if (G_IsFullScreen) {
		windowStyle = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; //dạng fullscreen
	}
	else {
		windowStyle = WS_OVERLAPPEDWINDOW; //dạng cửa sổ
	}

	G_hWnd =
		CreateWindow(
			GAME_NAME,
			GAME_NAME,
			windowStyle,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			G_ScreenWidth,
			G_ScreenHeight,
			NULL,
			NULL,
			G_hInstance,
			NULL);

	if (!G_hWnd) {
		DWORD ErrCode = GetLastError();
		return false;
	}

	ShowWindow(G_hWnd, nCmdShow);
	UpdateWindow(G_hWnd);
	return true;
}

bool CGame::InitD3D9()
{
	G_lpDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
	d3dpp.BackBufferWidth = G_ScreenWidth;    // set the width of the buffer
	d3dpp.BackBufferHeight = G_ScreenHeight;    // set the height of the buffer
	//d3dpp.hDeviceWindow = G_hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferCount = 1;
	if (G_IsFullScreen)
	{
		d3dpp.Windowed = FALSE;    // program fullscreen, not windowed		
	}
	else
	{
		d3dpp.Windowed = TRUE;
	}
	G_lpDirect3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		G_hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&G_lpDirect3DDevice);
	if (G_lpDirect3DDevice == NULL)
		return false;

	//backbuffer.......
	G_lpDirect3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &G_BackBuffer);
	D3DXCreateSprite(G_lpDirect3DDevice, &G_SpriteHandler);
	return true;
	
}

void CGame::GameInit()
{
	if(!InitWindow(ncmdShow))
		MessageBox(G_hWnd,L"Error to initialize",L"error",MB_OK);
	if(!InitD3D9())
		MessageBox(G_hWnd, L"Error to initiaze D3D9", L"error", MB_OK);
	KeyBoard::GetKey()->InitKeyboard();
	GTexture* texture = new GTexture();
	backGround->loadTextTureFromFile(L"BD.jpg", D3DCOLOR_XRGB(0,0,0,0));
	texture->loadTextTureFromFile(L"caveman.bmp",D3DCOLOR_XRGB(255,0,255));
	Sprite = new GSprite(texture, 8, 2, 0);
	player = new Player(Sprite);
	camera = new GCamera(G_ScreenWidth, G_ScreenHeight, 0, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	map->Init(L"Data/lv1.png", "Data/lv1-MAP.txt", "Data/lv1-MAP-quadtree.txt");
	GTexture* t = new GTexture();
	t->loadTextTureFromFile(L"lv1.png", D3DCOLOR_XRGB(255, 0, 255));
	test = new GSprite(t, 9, 6,0);
	simon->LoadResource(L"Resources/simon.png", 8, 3, 0);
	Font::GetFont()->Innit();
	objManager->Init("Data/lv1-GameObj.txt","Data/lv1-GameObj-Quadtree.txt");
	Tile::GetStaticObj()->Init();
	BigCandel::GetStaticObj()->Init();
	SmallCandle::GetStaticObj()->Init();
	Stair::GetStaticObj()->Init();
	TopStair::GetStaticObj()->Init();
	Effect::GetStaticObj()->Init();
	EnemyRender::GetStaticObj()->Init();
}

void CGame::GameRun()
{
	MSG msg;
	int done = 0;
	
	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 1000/60;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		_DeltaTime = now - frame_start;
		if (_DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			KeyBoard::GetKey()->ProcessKeyBoard();
							
			camera->Update(simon->GetX(), G_ScreenHeight / 2, simon->GetLayerMap());
			map->SelectScene(camera->GetRectCamera());

			objManager->UpDate(camera->GetRectCamera());
			simon->Update(objManager->GetListObj(),objManager->GetListInfo());
			
			RenderFrame(G_lpDirect3DDevice, _DeltaTime);
		
		}					
	}
}

void CGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{

	if (G_lpDirect3DDevice->BeginScene())
	{
		d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));

		

		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);	
		camera->SetTransForm();
		//backGround->RenderTexture(backGround->Width / 2, backGround->Height / 2);
		//player->Draw();

		//texture->RenderTexture(texture->Width / 2, texture->Height / 2);
		/*Sprite->Draw(0, 0);
		Sprite->Next();
		Sprite->Update(Delta);*/
		//test->SetFormat(D3DXVECTOR2(4, 4), 0, 1);
		//test->Draw(0, 100, 14);

		//map->DrawMap();
		
		objManager->Draw();
		simon->Draw(Delta);
		char str[100];		
		G_SpriteHandler->End();

		G_lpDirect3DDevice->EndScene();
	}
	G_lpDirect3DDevice->Present(NULL, NULL, NULL, NULL);
	blackBoard->RenderFrame(Delta);
}


void CGame::GameEnd()
{
	if (G_lpDirect3D != NULL) G_lpDirect3D->Release();
	if (G_lpDirect3DDevice != NULL) G_lpDirect3DDevice->Release();
}

CGame::~CGame()
{
}
