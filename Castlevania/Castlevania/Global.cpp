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

RECT LV5_STAGE1{ 0,16,1024,192 };
RECT LV5_STAGE2{ 512,240, 1792 +512, 416 };
RECT LV5_STAGE3{ 768,464,1536 + 768,640 };
RECT LV5_STAGE4{ 768,688,512 + 768,864 };

int G_Stage = 1;
bool Islockcamera =false;
int G_bossHP = 16;
bool NextLevel =false;
long G_ScoreValue = 0;


