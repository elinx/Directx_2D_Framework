#include "Game.h"

bool g_ctrlKeyPressed = false;
bool g_laltKeyPressed = false;

CGame::CGame(HINSTANCE hInstance, HWND hwnd):
	m_hInstance(hInstance),
	m_hwnd(hwnd),
	m_fps(0.0f)
{
	m_pGFX = new CGraphics(hwnd);
	m_pframeChecker = new CFrameChecker();//set up a timer
	m_pInput = new CInput();
	m_pDirectSound = new CDirectSound();
	m_pDogAgent = new CBonzeDogAgent();
}

CGame::~CGame()
{
	if(m_pGFX != NULL)
	{
		delete m_pGFX;
		m_pGFX = NULL;
	}
	if (m_pframeChecker != NULL)
	{
		delete m_pframeChecker;
		m_pframeChecker = NULL;
	}
	if(m_pframeChecker != NULL)
	{
		delete m_pframeChecker;
		m_pframeChecker = NULL;// this line can't be missed, cos if you delete this pointer again and 
		// this pointer is not null, it will cos an error.
	}
	delete m_pInput;
	m_pInput = NULL;

	delete m_pDirectSound;
	m_pDirectSound = NULL;

	delete m_pDogAgent;
	m_pDogAgent = NULL;
}

int CGame::GameInit()
{
	if(m_pGFX->GraphicsInit() != D3D_OK)
		return E_FAIL;
	if(! m_pInput->InitDirectInput(m_hInstance, m_hwnd))
		return E_FAIL;
	if(! m_pDirectSound->InitDirectSound(m_hwnd))
		return E_FAIL;

	m_pDirectSound->LoadWaveData(std::wstring(L"./Assets/Windows XP Æô¶¯.wav"));
	m_pDirectSound->StartToPlay();

	m_pDogAgent->InitAgent(this->m_pGFX);

	return D3D_OK;
}

void CGame::GameExecute()
{
	FrameBegin();	
	FrameExecute();
	FrameEnd();
}

void CGame::GameFinish()
{

}

/*
	The game begin to run, do some graphics job and other stuffs
*/
void CGame::FrameBegin()
{
	m_pframeChecker->StartTimer();
	m_pGFX->BeginRender();
}

void CGame::FrameExecute()
{
	// draw the background, Show a battle field png/jpeg file.
	m_pGFX->UpdateBackground();

	// draw the header title.
	RECT rect = {HEADER_ORGPOS_X, HEADER_ORGPOS_Y, HEADER_WIDTH, HEADER_ORGPOS_Y + HEADER_FONT_HEIGHT};
	m_pGFX->DrawText(FONT_HEADERFONT, &rect, L"Kill The Monster\n", D3DCOLOR_XRGB(0, 0, 0));

	// Show the position of the cursor
	ShowCursorInfo();

	if(m_pInput->IsKeyPressed(DIK_LCONTROL))
		g_ctrlKeyPressed = true;
	else
		g_ctrlKeyPressed = false;

	if(m_pInput->IsKeyPressed(DIK_LALT))
		g_laltKeyPressed = true;
	else
		g_laltKeyPressed = false;
	/***********************************************************
	 * Agent code below
	 ***********************************************************/
	m_pDogAgent->Run();

	//If escape key pressed, close the window.
	if(m_pInput->IsKeyPressed(DIK_ESCAPE))
		DestroyWindow(m_hwnd);
}
/*
	The game comes to an end, do some graphics clearing job and other stuffs
*/
void CGame::FrameEnd()
{
	// Calculate fame per second.
	double fps =1.0f / m_pframeChecker->GetFrametime();
	double diff = m_fps - fps;
	if(diff > 0.50f || diff < -0.50f) m_fps = fps;

	std::wstringstream wsstr;
	wsstr << L"Frame Per Second: " << std::fixed << std::setprecision(2) << m_fps ;
	RECT	rect = {0, HEADER_FONT_HEIGHT, HEADER_WIDTH, HEADER_FONT_HEIGHT + HEADER_FONT_HEIGHT};

	m_pGFX->DrawText(FONT_NORMALFONT, &rect, wsstr.str(), D3DCOLOR_XRGB(255, 255, 0));

	m_pGFX->EndRender();
}

void CGame::ShowCursorInfo()
{
		//Get the cursor postion
	POINT	cursorPos;
	long dummy;
	m_pInput->GetMouseRelativePosition(cursorPos.x, cursorPos.y, dummy);
	//Show information about cursor position
	RECT rect1 = { 0, HEADER_FONT_HEIGHT * 2, HEADER_WIDTH, HEADER_FONT_HEIGHT * 2 + HEADER_FONT_HEIGHT};
	std::wstringstream	wstream;
	wstream << L"Mouse Position X: " << std::setw(4) << cursorPos.x << L"    Y: " << std::setw(4) << cursorPos.y;
	m_pGFX->DrawText(FONT_NORMALFONT, &rect1, wstream.str(), D3DCOLOR_XRGB(255, 0, 0));
}