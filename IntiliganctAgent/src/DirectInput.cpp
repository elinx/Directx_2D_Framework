#include "DirectInput.h"

const unsigned int CInput::m_iKeyStateLen = 256;

CInput::CInput()
	:
m_hwnd(0),
m_ipDirectInput(NULL)
{
	m_pKeyState = new unsigned char[m_iKeyStateLen];// allocate memory for the array
	m_lMouseX = 0;
	m_lMouseY = 0;
	m_lMouseZ = 0;
	ZeroMemory(&m_sMouseState, sizeof(m_sMouseState));
}

CInput::~CInput()
{
	if (m_ipDirectInput != NULL)
	{
		m_ipDirectInput->Release();
		m_ipDirectInput = NULL;
	}
	if (m_ipKeyboard != NULL)
	{
		m_ipKeyboard->Unacquire();
		m_ipKeyboard->Release();
		m_ipKeyboard = NULL;
	}
	if (m_ipMouse != NULL)
	{
		m_ipMouse->Unacquire();
		m_ipMouse->Release();
		m_ipMouse = NULL;
	}
	delete [] m_pKeyState;	// after delete the pointer, the value of the pointer is not changed
	m_pKeyState = NULL;
}
/*
	Create the main DirectInput object
*/
bool CInput::InitDirectInput(HINSTANCE hInstance, HWND hwnd)
{
	//	Create the main DirectInput object
	if (FAILED(DirectInput8Create(hInstance, 
					DIRECTINPUT_VERSION, 
					IID_IDirectInput8,
					(LPVOID*)&m_ipDirectInput,// equal to void** (&m_ipDirectInput)
					NULL)))
	{
		MessageBox(hwnd,
			L"DirectInput8Create() failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	if(! InitKeyboard(hwnd))
		return false;

	if(! InitMouse(hwnd))
		return false;

	return true;
}
bool CInput::InitKeyboard(HWND hwnd)
{
	// initialize the keyboard device
	if (FAILED(m_ipDirectInput->CreateDevice(GUID_SysKeyboard, &m_ipKeyboard, NULL)))
	{
		MessageBox(hwnd,
			L"Create Keyboard Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// Set the keyboard device data format
	if(FAILED(m_ipKeyboard->SetDataFormat(&c_dfDIKeyboard)))// a global variable
	{
		MessageBox(hwnd,
			L"Set Keyboard Data Format Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// Set the keyboard device(hardware) shared level
	if(FAILED(m_ipKeyboard->SetCooperativeLevel(hwnd, 
				DISCL_FOREGROUND | // only used when the program in active mode
				DISCL_EXCLUSIVE))) // when the program in use, other program can't use the keyboard
	{
		MessageBox(hwnd,
			L"Set Keyboard Cooperative Level Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// Now acquire the keyboard.
	if(FAILED(m_ipKeyboard->Acquire()))
	{
		MessageBox(hwnd,
			L"Acquire Keyboard Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	return true;
}

bool CInput::InitMouse(HWND hwnd)
{
	m_hwnd = hwnd;
	// initialize the mouse device
	if (FAILED(m_ipDirectInput->CreateDevice(GUID_SysMouse, &m_ipMouse, NULL)))
	{
		MessageBox(hwnd,
			L"Create Mouse Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// Set the mouse device data format
	if(FAILED(m_ipMouse->SetDataFormat(&c_dfDIMouse)))// a global variable
	{
		MessageBox(hwnd,
			L"Set Mouse Data Format Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// Set the mouse device(hardware) shared level
	if(FAILED(m_ipMouse->SetCooperativeLevel(hwnd, 
		DISCL_FOREGROUND | // only used when the program in active mode
		DISCL_NONEXCLUSIVE))) // when the program in use, other program CAN use the mouse OR the mouse cursor is lost
	{
		MessageBox(hwnd,
			L"Set Mouse Cooperative Level Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	// Now acquire the mouse.
	if(FAILED(m_ipMouse->Acquire()))
	{
		MessageBox(hwnd,
			L"Acquire Mouse Failed!",
			L"ERROR",
			MB_OK);
		return false;
	}
	return true;
}

// to check if the specific key is pressed
bool CInput::IsKeyPressed(unsigned char key)
{
	// lost recovery method
	if(! ReadKeyboardState())
		return false;
	else
		return ((m_pKeyState[key] & 0x80) ? true : false);
}

// read the keyboard device
bool CInput::ReadKeyboardState()
{
	HRESULT  hr = m_ipKeyboard->GetDeviceState(m_iKeyStateLen, (LPVOID)m_pKeyState);////?????????
	if (FAILED(hr))// if this two failure happens, try to re-acquire the device
	{
		if(hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
			m_ipKeyboard->Acquire();
		else
			return false;
	}
	return true;
}
// if the mouse key 0~3 is pressed
bool CInput::IsMouseKeyPressed(unsigned char key)
{
	// lost recovery method
	if(! ReadMouseState())
		return false;
	else
		return ((m_sMouseState.rgbButtons[key] & 0x80) ? true : false);
}
void CInput::GetMouseAbsolutePosition(long& x, long& y, long& z)
{
	ReadMouseState();
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_lMouseX += m_sMouseState.lX;
	m_lMouseY += m_sMouseState.lY;
	m_lMouseZ += m_sMouseState.lZ;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if(m_lMouseX < 0)  m_lMouseX = 0;
	if(m_lMouseY < 0)  m_lMouseY = 0;

	if(m_lMouseX > WND_WIDTH)  m_lMouseX = WND_WIDTH;
	if(m_lMouseY > WND_HEIGHT) m_lMouseY = WND_HEIGHT;

	x = m_lMouseX;
	y = m_lMouseY;
	z = m_lMouseZ;
}
void CInput::GetMouseRelativePosition(long& x, long& y, long& z)
{
	//ReadMouseState();
	//x = m_sMouseState.lX;
	//y = m_sMouseState.lY;
	//z = m_sMouseState.lZ;
	POINT	cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(m_hwnd, &cursorPos);
	x = cursorPos.x;
	y = cursorPos.y;
}
bool CInput::ReadMouseState()
{
	HRESULT  hr = m_ipMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_sMouseState);
	if (FAILED(hr))// if this two failure happens, try to re-acquire the device
	{
		if(hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
			m_ipMouse->Acquire();
		else
			return false;
	}
	return true;
}