#pragma once

#include <d3d9.h>
#include <dinput.h>
#include "WinConfigure.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class CInput {
public:
	CInput();
	~CInput();

	bool InitDirectInput(HINSTANCE hInstance, HWND hwnd);

	bool IsKeyPressed(unsigned char key);
	bool IsMouseKeyPressed(unsigned char key);
	void GetMouseAbsolutePosition(long& x, long& y, long& z);
	void GetMouseRelativePosition(long& x, long& y, long& z);

private:
	bool InitKeyboard(HWND hwnd);
	bool InitMouse(HWND hwnd);
	bool ReadKeyboardState();
	bool ReadMouseState();

private:
	HWND					m_hwnd;
	IDirectInput8*			m_ipDirectInput;
	LPDIRECTINPUTDEVICE8	m_ipKeyboard;
	LPDIRECTINPUTDEVICE8	m_ipMouse;

	unsigned char*			m_pKeyState;
	static const unsigned int			
							m_iKeyStateLen;
	DIMOUSESTATE			m_sMouseState;
	long					m_lMouseX, m_lMouseY, m_lMouseZ;
};