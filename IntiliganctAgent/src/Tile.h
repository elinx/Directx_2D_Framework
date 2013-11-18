#pragma once

#include <string>
#include <d3d9.h>
#include <vector>
#include <assert.h>
#include "Texture.h"
/* 
 * 这里的texture index用于定位texture所在的数组的位置，
 * 而tile index用于定位tile所在的texture
 */
class CTile {
public:
	CTile();
	~CTile();

	// Functions to create and free the tile interface
    bool Create(IDirect3DDevice9* ipDevice, int TexturesCount);
    bool Free();

    // Functions to load and free a single texture
    bool Load(int TextureIndex, std::wstring wstrFilename,int firstGrid,
			  int imageWidth, int imageHeight,
              int TileWidth = 0, int TileHeight = 0,//tile or texture?
              D3DCOLOR Transparent = 0,
              D3DFORMAT Format = D3DFMT_A8R8G8B8);
    bool Free(int TextureIndex);

    // Functions to retrieve tile dimensions and 
    // # of tiles in a texture.
    int GetWidth(int TextureIndex);
    int GetHeight(int  TextureIndex);
    int GetCount(int Textureindex);

    // Draw a single tile to location
    bool Draw(int TextureIndex, int TileIndex,                 
              int ScreenX, int ScreenY,                    
              D3DCOLOR Color = 0xFFFFFFFF,                   
              float XScale = 1.0f, float YScale = 1.0f);

	int FindTextureByTileIndex(int tileIndex);				// Find the texture that hold the tile for the specific index
	void BuildTileAt(int tileIndex, IDirect3DSurface9* m_ipMapSruface, int mapX, int mapY);// copy the tile into the specific pos of map
private:
	IDirect3DDevice9*			m_ipDevice;					// hold a reference of the graphic device
	int							m_TexturesCount;			// # of textures(size of the vector below is determinzed by this number)
	std::vector<CTexture*>*		m_vpTilesetTexture;			// Read the tileset images and load them into this texture vector
    std::vector<int>*			m_viWidths;					// Tile widths array
    std::vector<int>*			m_viHeights;				// Tile heights array
    std::vector<int>*			m_viColumns;				// # columns in texture
	std::vector<int>*			m_viFirstGridNum;			// firstgrid of each texture
};