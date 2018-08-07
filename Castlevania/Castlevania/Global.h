#ifndef _Global_H_
#define _Global_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <d3d9.h>
#include "GSurface.h"


#define GAME_NAME L"FrameWork"
//size of key buffer(used in game class to save key state
#define GL_KEY_BUFFER_SIZE	1024

extern int G_ScreenWidth;
extern int G_ScreenHeight;
extern bool G_IsFullScreen;

extern HINSTANCE G_hInstance;
extern HWND G_hWnd;

extern LPDIRECT3D9 G_lpDirect3D;
extern LPDIRECT3DDEVICE9 G_lpDirect3DDevice;
extern LPD3DXSPRITE G_SpriteHandler;
extern LPDIRECTINPUT8 G_DirectInput;
extern LPDIRECTINPUTDEVICE8 G_KeyBoard;

extern LPDIRECT3DSURFACE9 G_BackBuffer;

//Map
extern RECT lv2_Layer1;
extern RECT lv2_Layer2;
extern RECT lv2_Layer3;
extern RECT lv2_Layer4;
extern int G_Stage;
extern bool Islockcamera;
extern int G_bossHP;
extern bool NextLevel;
extern long G_ScoreValue;


#endif

