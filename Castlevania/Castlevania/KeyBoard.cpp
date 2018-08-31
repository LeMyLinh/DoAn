#include "KeyBoard.h"


KeyBoard* KeyBoard::_keyBoard = 0;

KeyBoard::KeyBoard()
{

}

KeyBoard * KeyBoard::GetKey()
{
	if (_keyBoard == 0)
		_keyBoard = new KeyBoard();
	return _keyBoard;
}

void KeyBoard::InitKeyboard()
{
	HRESULT
		hr = DirectInput8Create
		(
			GetModuleHandle(NULL),
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&G_DirectInput, NULL
		);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return;

	hr = G_DirectInput->CreateDevice(GUID_SysKeyboard, &G_KeyBoard, NULL);

	// TO-DO: put in exception handling
	if (FAILED(hr) == true)
		return;

	hr = G_KeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr) == true)
		return;

	hr = G_KeyBoard->SetCooperativeLevel(G_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr) == true)
		return;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = GL_KEY_BUFFER_SIZE;

	hr = G_KeyBoard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr) == true)
		return;

	hr = G_KeyBoard->Acquire();
	if (FAILED(hr) == true)
		return;
}

void KeyBoard::ProcessKeyBoard()
{
	HRESULT hr = G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
	if (hr != S_OK)
	{
		hr = G_KeyBoard->Acquire();
		G_KeyBoard->GetDeviceState(sizeof(_KeyStates), (LPVOID)&_KeyStates);
	}
	// Collect all key states first
	G_KeyBoard->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	if (IsKeyDown(DIK_ESCAPE))
	{
		PostMessage(G_hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = GL_KEY_BUFFER_SIZE;
	hr = G_KeyBoard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);
	}
}

void KeyBoard::OnKeyUp(int KeyCode)
{

}

void KeyBoard::OnKeyDown(int KeyCode)
{

}


int KeyBoard::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}


KeyBoard::~KeyBoard()
{
}
