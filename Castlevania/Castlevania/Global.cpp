#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include "GSurface.h"


int G_ScreenWidth = 550;
int G_ScreenHeight = 480;
bool G_IsFullScreen = false;

HINSTANCE G_hInstance;
HWND G_hWnd;

LPDIRECT3D9 G_lpDirect3D;
LPDIRECT3DDEVICE9 G_lpDirect3DDevice;
LPDIRECT3DSURFACE9 G_BackBuffer;
LPD3DXSPRITE G_SpriteHandler;
LPDIRECTINPUT8 G_DirectInput;
LPDIRECTINPUTDEVICE8 G_KeyBoard;

RECT STAGE1{ 0,48,2816,48 + 176 };
RECT STAGE2{ 1537,272,1537 + 512, 272 + 176 };
RECT STAGE3{ 0,272,752, 272 + 176 };
RECT STAGE4{ 0, 0, 0, 0 };

int G_Stage = 1;
bool Islockcamera =false;
int G_bossHP = 16;
bool NextLevel =false;
long G_ScoreValue = 0;


