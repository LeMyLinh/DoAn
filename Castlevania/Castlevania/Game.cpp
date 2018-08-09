#include "Game.h"
#include "Global.h"
#include "GTexture.h"
#include <Windows.h>
#include <cstdlib> 
#include <ctime> 
#include <dinput.h>

CGame::CGame(int _ncmdShow)
{
	ncmdShow = _ncmdShow;
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
	if (!InitWindow(ncmdShow))
		MessageBox(G_hWnd, L"Error to initialize", L"error", MB_OK);
	if (!InitD3D9())
		MessageBox(G_hWnd, L"Error to initiaze D3D9", L"error", MB_OK);

	InitKeyboard();
	this->LoadResources(G_lpDirect3DDevice);
}

void CGame::GameRun()
{
	MSG msg;
	int done = 0;

	DWORD frame_start = GetTickCount();;

	DWORD tick_per_frame = 1000 / 60;

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
			UpdateGame(G_lpDirect3DDevice, _DeltaTime);
			RenderFrame(G_lpDirect3DDevice, _DeltaTime);

		}
		ProcessKeyBoard();

		ProcessInput(G_lpDirect3DDevice, _DeltaTime);
	}
}

void CGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{

	if (G_lpDirect3DDevice->BeginScene())
	{
		d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));



		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		G_SpriteHandler->End();

		G_lpDirect3DDevice->EndScene();
	}
	G_lpDirect3DDevice->Present(NULL, NULL, NULL, NULL);
	//blackBoard->RenderFrame(Delta);
}


void CGame::GameEnd()
{
	if (G_lpDirect3D != NULL) G_lpDirect3D->Release();
	if (G_lpDirect3DDevice != NULL) G_lpDirect3DDevice->Release();
}

CGame::~CGame()
{
}



void CGame::InitKeyboard()
{
    HRESULT 
		hr = DirectInput8Create
			( 
				GetModuleHandle(NULL), 
				DIRECTINPUT_VERSION, 
				IID_IDirectInput8, (VOID**)&G_DirectInput, NULL 
			);

	// TO-DO: put in exception handling
	if (FAILED(hr)==true)
		return;
	
	hr = G_DirectInput->CreateDevice(GUID_SysKeyboard, &G_KeyBoard, NULL); 
	
	// TO-DO: put in exception handling
	if (FAILED(hr)==true) 
		return;

	hr = G_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)==true) 
		return;

	hr = G_KeyBoard->SetCooperativeLevel(G_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	if (FAILED(hr)==true) 
		return;

    DIPROPDWORD dipdw;

    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = GL_KEY_BUFFER_SIZE;

    hr = G_KeyBoard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if (FAILED(hr)==true) 
		return;

	hr = G_KeyBoard->Acquire(); 
	if (FAILED(hr)==true) 
		return;
}


void CGame::ProcessKeyBoard()
{
		HRESULT hr = G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		if(hr != S_OK)
		{
			hr = G_KeyBoard->Acquire();
			G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		}
		// Collect all key states first
		G_KeyBoard->GetDeviceState( sizeof(_KeyStates), _KeyStates);

		if (IsKeyDown(DIK_ESCAPE)) 
		{
			PostMessage(G_hWnd,WM_QUIT,0,0);
		}

		// Collect all buffered events
		DWORD dwElements = GL_KEY_BUFFER_SIZE;
		hr = G_KeyBoard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0 );

		// Scan through all data, check if the key is pressed or released
		for( DWORD i = 0; i < dwElements; i++ ) 
		{
			int KeyCode = _KeyEvents[i].dwOfs;
			int KeyState = _KeyEvents[i].dwData;
			if ( (KeyState & 0x80) > 0)
				OnKeyDown(KeyCode);
			else 
				OnKeyUp(KeyCode);
		}
}

void CGame::OnKeyUp(int KeyCode) { }
void CGame::OnKeyDown(int KeyCode) { }

// Main game message loop

void CGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv) { }

void CGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta) 
{
	/*HRESULT hr = G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		if(hr != S_OK)
		{
			hr = G_KeyBoard->Acquire();
			G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
		}*/
}

void CGame::UpdateGame(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
}

int CGame::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

