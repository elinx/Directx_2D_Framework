#pragma once

#include <string>
#include <sstream>
#include <assert.h>
#include <iomanip>
#include <D3dx9tex.h>
#include "WinConfigure.h"
#include <boost/thread.hpp>

#pragma comment(lib, "D3dx9.lib")

//extern boost::mutex	gGraphic_Mutex;

class CSprite {
public:
	// Ctor adn detor
	CSprite(IDirect3DDevice9* ipDevice, std::wstring filePath, int width, int height);
	~CSprite();

	// Just Draw the sprite on the screen at the pos(x, y) position
	void DrawBitmap(D3DXVECTOR3* pos, D3DCOLOR mask, bool reverse = false);
private:
	ID3DXSprite*			m_ipSprite;
	LPDIRECT3DTEXTURE9		m_ipTexture;
	IDirect3DDevice9*		m_ipDevice;
	std::wstring			m_filePath;

	int						m_iWidth;
	int						m_iHeight;
};