#include <Windows.h>
#include "Game.h"
#include "WinConfigure.h"

IDirect3DDevice9*		g_ipDevice = NULL; // this device interface is so god damn powerfull!!!!

LRESULT CALLBACK WinProCallBack(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

int WINAPI WinMain(  _In_  HINSTANCE hInstance,
	_In_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow )
{
	WNDCLASS wndclass;
	HWND hwnd;
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	wndclass.style			= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc	= WinProCallBack;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);              // predefined app. icon 
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);                  // predefined arrow  
	wndclass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);;
	wndclass.lpszMenuName	= NULL;
	wndclass.hInstance		= hInstance;
	wndclass.lpszClassName	= L"Created_By_Elinxed.";

	RegisterClass(&wndclass);

	hwnd = CreateWindow(wndclass.lpszClassName, 
		L"Elinx_Framework", 
		WS_OVERLAPPEDWINDOW, // top-level window 
		WND_ORIGINPOS_X,       // default horizontal position 
		WND_ORIGNIPOS_Y,       // default vertical position 
		WND_WIDTH,				// default width 
		WND_HEIGHT + 24,       // default height, while 24 is height of the caption bar
		NULL,      // no owner window 
		NULL,      // use class menu 
		hInstance, // handle to application instance 
		NULL);     // no window-creation data 
	
	if (!hwnd)
		return false;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	CGame	game(hInstance, hwnd);
	game.GameInit();

	while(TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// 为什么这里不能是hwnd呢？
		{
			if(msg.message == WM_QUIT)	break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			game.GameExecute();
	}

	game.GameFinish();
	UnregisterClass(wndclass.lpszClassName, hInstance);
	return 0;
}

LRESULT CALLBACK WinProCallBack(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}break;			
		case VK_DOWN:
		{
			if (wParam == VK_ESCAPE)
				DestroyWindow(hwnd);
		}break;	
		case WM_SETCURSOR:
			if(g_ipDevice)
			{
				SetCursor(NULL);
				g_ipDevice->ShowCursor(TRUE);
				return 0;// if not return here, the cursor will be setted to original shape again.
			}
			break;
		default:
			break;
	}	
	return DefWindowProc(hwnd,message,wParam,lParam);
}