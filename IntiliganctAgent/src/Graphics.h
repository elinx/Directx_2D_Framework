#pragma once

//////////////////////////////////////////////////////////////////////////
// all basic operations about graphics are here.
// implement the graphics object as a singleton.
//////////////////////////////////////////////////////////////////////////

#include <d3d9.h>
#include <D3dx9core.h>
#include "WinConfigure.h"
#include <string>
#include "Font.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

#pragma	comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class CGraphics {
public:
	CGraphics();
	CGraphics(HWND hwnd);
	~CGraphics();

	int GraphicsInit();
	void BeginRender();
	void EndRender();

	
	//	use the loadXXX method before use draw method.
	void	DrawText(const int FONTTYPE, RECT *rect, std::wstring str, D3DCOLOR color);
	void	DrawSprite(const int SPRITE_TYPE, int x, int y, D3DCOLOR mask);

	// load the sprite information into the ppanimaion struct
	void	LoadAnimation(std::wstring fileBase, int frameCount, CAnimatedSprite** ppAnimation, int width, int height){
			*ppAnimation = new CAnimatedSprite(m_ipDevice);	// the outer fucntion did not has this reference
			(*ppAnimation)->LoadSprites(fileBase, frameCount, width, height);
	}

	void	UpdateBackground();
	void	SetCursorPosition(int x, int y);
private:
	//	FONT LOAD INTO THIS SYSTEM.
	CFont*	LoadFont(int height, int width, int weight, bool italic, std::wstring faceName, std::wstring *filePath = NULL);
	void	DeleteFont();
	int		FontInit();	

	int		SpriteInit();
	CSprite*LoadSprite(std::wstring filePath, int width, int height);
	void	DeleteSprite();
	bool	InitBackgroundSurface();/// for background
	bool	InitCursorSurface();// for cursor

private:
	IDirect3D9*				m_ipDirect;		// main interface, get other interfaces through this interface 
	IDirect3DDevice9*		m_ipDevice;		// main graphic device interface, render frames through this interface
	HWND					m_hwnd;		

	CFont*					m_pFont[FONTSNUM];		// THREE KINDS OF FONT IN THIS SYSTEM
	//CSprite*				m_pSprite[SPRITESNUM];

	IDirect3DSurface9* 		m_pBackBufferSurface;
	IDirect3DSurface9*		m_pImageSurface;
	IDirect3DSurface9*		m_pCursorSurface;
};