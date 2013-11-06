#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <D3dx9tex.h>
#include "WinConfigure.h"

#pragma comment(lib, "D3dx9.lib")

class CSprite {
public:
	CSprite(IDirect3DDevice9* ipDevice, std::wstring filePath, int width, int height)
		:
	m_ipDevice(ipDevice),
	m_filePath(filePath)
	{
		D3DXCreateTextureFromFileEx(m_ipDevice, filePath.c_str(), width, height,
			D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
			D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 255, 255), 
			NULL, NULL,&m_ipTexture);// create and load the bitmap.
		D3DXCreateSprite(m_ipDevice, &m_ipSprite);
	}
	~CSprite()
	{
		if (m_ipTexture != NULL)
		{
			m_ipTexture->Release();
			m_ipTexture = NULL;
		}
		if (m_ipSprite != NULL)
		{
			m_ipSprite->Release();
			m_ipSprite = NULL;
		}
	}
	void DrawBitmap(D3DXVECTOR3* pos, D3DCOLOR mask)
	{
		m_ipSprite->Begin(D3DXSPRITE_ALPHABLEND);
		m_ipSprite->Draw(m_ipTexture, NULL, NULL, pos, mask);
		m_ipSprite->End();
	}
private:
	ID3DXSprite*			m_ipSprite;
	LPDIRECT3DTEXTURE9		m_ipTexture;
	IDirect3DDevice9*		m_ipDevice;
	std::wstring			m_filePath;
};