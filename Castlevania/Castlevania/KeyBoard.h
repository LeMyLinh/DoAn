#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
#include <dinput.h>
#include "Global.h"

class KeyBoard
{
private:
	static KeyBoard* _keyBoard;
	BYTE  _KeyStates[256];
	DIDEVICEOBJECTDATA _KeyEvents[GL_KEY_BUFFER_SIZE]; // Buffered keyboard data
public:
	KeyBoard();

	static KeyBoard* GetKey();
	void InitKeyboard();
	void ProcessKeyBoard();
	virtual void OnKeyUp(int KeyCode);
	virtual void OnKeyDown(int KeyCode);
	int IsKeyDown(int KeyCode);

	~KeyBoard();
};

#endif // !_KEYBOARD_H_

