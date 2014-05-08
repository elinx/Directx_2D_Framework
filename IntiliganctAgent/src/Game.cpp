#include "Game.h"

extern CInput* g_pDirectInput;
//bool g_ctrlKeyPressed = false;
//bool g_laltKeyPressed = false;

CGame::CGame(HINSTANCE hInstance, HWND hwnd):
	m_hInstance(hInstance),
	m_hwnd(hwnd),
	m_fps(0.0f)
{
	m_pGFX = new CGraphics(hwnd);
	m_pframeChecker = new CFrameChecker();//set up a timer
	m_pInput = new CInput();
	g_pDirectInput = m_pInput;// Init the input handler to global scope
	m_pDirectSound = new CDirectSound();
	m_pDogAgent = new CBonzeDogAgent();
	m_pMap = new CMap();
	m_pCamera = new CCamera(m_pDogAgent->GetAgentPosX(), m_pDogAgent->GetAgentPosY());
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

	delete m_pMap;
	m_pMap = NULL;

	delete m_pCamera;
	m_pCamera = NULL;
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

	if(!m_pMap->LoadMap(m_pGFX->GetD3DDevice(), L"./Assets/tileset/formalMap.json"))
		return E_FAIL;

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
	// Draw the background, Show a battle field png/jpeg file
	// m_pGFX->UpdateBackground();

	m_pCamera->Update(m_pDogAgent->GetRelativeX(), m_pDogAgent->GetRelativeY());
	m_pMap->DrawMap(m_pCamera->GetPosX(), m_pCamera->GetPosY());

	// Draw the header title.
	ShowHeaderInfo();
	// Show the position of the cursor
	ShowCursorInfo();
	// Show the position of the agent
	ShowAgentInfo();
	/***********************************************************
	 * Agent code below
	 ***********************************************************/
	m_pDogAgent->Run(m_pCamera->GetPosX(), m_pCamera->GetPosY());

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
void CGame::ShowHeaderInfo()
{
	RECT rect = {HEADER_ORGPOS_X, HEADER_ORGPOS_Y, HEADER_WIDTH, HEADER_ORGPOS_Y + HEADER_FONT_HEIGHT};
	m_pGFX->DrawText(FONT_HEADERFONT, &rect, L"Kill The Monster\n", D3DCOLOR_XRGB(0, 0, 0));
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

void CGame::ShowAgentInfo()
{
	//Get the cursor postion
	int x, y, rx, ry, cx, cy;
	x = m_pDogAgent->GetAgentPosX();
	y = m_pDogAgent->GetAgentPosY();
	rx = m_pDogAgent->GetRelativeX();
	ry = m_pDogAgent->GetRelativeY();
	cx = m_pCamera->GetPosX();
	cy = m_pCamera->GetPosY();
	//Show information about cursor position
	RECT rect1 = { 0, HEADER_FONT_HEIGHT * 3, HEADER_WIDTH, HEADER_FONT_HEIGHT * 3 + HEADER_FONT_HEIGHT * 2};
	std::wstringstream	wstream;
	wstream << L"Agent Position(window) X: " << std::setw(4) << x << L"    Y: " << std::setw(4) << y << std::endl;
	wstream << L"Agent Relative Position(window) X: " << std::setw(4) << rx << L"    Y: " << std::setw(4) << ry << std::endl;
	wstream << L"Camera Position(map) X: " << std::setw(4) << cx << L"    Y: " << std::setw(4) << cy << std::endl;
	m_pGFX->DrawText(FONT_NORMALFONT, &rect1, wstream.str(), D3DCOLOR_XRGB(0, 7, 153));
}