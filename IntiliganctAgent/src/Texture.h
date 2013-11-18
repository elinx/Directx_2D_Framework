#pragma once

#include <d3d9.h>
#include <D3dx9core.h>
#include <assert.h>
#include <string>
#include <vector>
//#include "Graphics.h"

class CTexture {
public:
	CTexture();
	~CTexture();

    IDirect3DTexture9 *GetTexture();

    bool LoadFromFile(IDirect3DDevice9* ipDevice, std::wstring wstrFilename, 
						int textureWidth, int textureHeight,
						DWORD Transparent = 0, 
						D3DFORMAT Format = D3DFMT_UNKNOWN);

    bool LoadFromTexture(IDirect3DDevice9* ipDevice, IDirect3DTexture9 *Texture);
    bool Free();

    bool      IsLoaded();

    int      GetWidth();
    int      GetHeight();
    D3DFORMAT GetFormat();

    bool Draw(long DestX, long DestY,                         
              long SrcX = 0, long SrcY = 0,                   
              long Width = 0, long Height = 0,                
              float XScale = 1.0f, float YScale = 1.0f,       
              D3DCOLOR Color = 0xFFFFFFFF);
	void GetTileCoordOnTexture(int tileIndex,int tileWidth,int tileHeight, int& tileTextureX, int& tileTextureY);
	void BuildTileAt(int tileIndex, int tileWidth,int tileHeight, 
			IDirect3DSurface9* m_ipMapSurface, int mapX, int mapY);
private:
	IDirect3DDevice9*		m_ipDevice;	//No need to keep a reference to the device pointer, but maybe need in the future?!
    IDirect3DTexture9*		m_Texture;
    int						m_Width, m_Height;
};