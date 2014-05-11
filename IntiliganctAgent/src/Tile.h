#pragma once

#include <string>
#include <d3d9.h>
#include <vector>
#include <assert.h>
#include "Texture.h"
/**
 * Description: 
 * 
 * 
 * Date: 2014-5-11
 */
class CTile {

public:

	CTile();
	CTile(IDirect3DDevice9* ipDevice, 
		  unsigned int id,
		  unsigned int w,
		  unsigned int h);
	CTile(const CTile& tile);
	~CTile();

	CTile&						operator=(const CTile& rhs);
	bool						operator==(const CTile& rhs);
	bool						operator!=(const CTile&rhs);

    unsigned int				GetWidth();
    unsigned int				GetHeight();
    unsigned int				GetID();

	HRESULT						LoadTile(std::wstring filePath);
	HRESULT						LoadTile(std::wstring filePath, int xoffset, int yoffset);
	HRESULT						LoadTile(CTexture& texture);

    HRESULT						Draw(int x,
									 int y,                  
								     D3DCOLOR Color = 0xFFFFFFFF,                   
								     float XScale = 1.0f, 
									 float YScale = 1.0f);
private:
	IDirect3DDevice9*			m_ipDevice;													// hold a reference of the graphic device
	
	CTexture*					m_pTexture;													// texture of the tile

    unsigned int				m_width;													// tile width
    unsigned int				m_height;													// tile height
    unsigned int				m_ID;														// tile id
};