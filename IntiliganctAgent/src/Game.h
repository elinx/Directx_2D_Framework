#pragma once

#include "Graphics.h"
#include "WinConfigure.h"
#include "FrameChecker.h"
#include "DirectInput.h"
#include "DirectSound.h"
#include "Agent.h"
#include "BonzeDogAgent.h"
#include "Map.h"
#include <sstream>
#include <iomanip>
#include <windef.h>
#include <cstdlib>
/*
	Main game entity, compose the frame.
*/
class CGame
{
public:
	CGame();
	CGame(HINSTANCE hInstance,HWND hwnd);
	~CGame();

	int GameInit();
	void GameExecute();
	void GameFinish();

	void FrameBegin();
	void FrameExecute();
	void FrameEnd();
private:
	void ShowCursorInfo();
protected:
private:
	HINSTANCE				m_hInstance;
	HWND					m_hwnd;
	CGraphics*				m_pGFX;
	
	CFrameChecker*			m_pframeChecker;
	double					m_fps;

	CInput*					m_pInput;
	CDirectSound*			m_pDirectSound;

	CBonzeDogAgent*			m_pDogAgent;
	CMap*					m_pMap;
};