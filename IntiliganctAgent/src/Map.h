#pragma once

#include <vector>
#include <string>
#include <d3d9.h>
#include <sstream>
#include "WinConfigure.h"
#include "Tile.h"
// What does the map need?
// 1: how many layers?
// 2: what's the w/h of each layer?
// 3: how many tiles?
// 4: what's the w/h of each tile?
// 5: what's the path of each tile, so that I can load it into the memory?
// 6: how to rearrange the tiles or what's the tile position?

class CMap {
	// Define a struct to hold the width and height information of each layer of a spefic map
public:
	CMap();
	~CMap();

	/* Types define below used to hold the map information of whole map */
	typedef struct _SLayerWH {
		int			width, height;
	}SRectWH;												// Define a rect struct to hold the w/h information

	typedef struct _slayer {
		std::vector<int>*	data;							// 2D vector pointer, store the layer index information of tiles
		SRectWH				layerWH;
		std::string			name, type;
		bool				visible;
		int					x, y;
	}SLayer;												// A layer struct to hold the w/h information of each layer

	typedef struct _tileset {
		int					firstGrid;
		std::string			image, name;
		SRectWH				imageWH, tileWH;				// A struct for tileset information
	}STileSet;

	bool LoadMap(IDirect3DDevice9* ipDevice, std::wstring wstrFilePath);

	/* Basic information */
	int	 GetMapTileCountW();								// Get How many tiles in a row
	int	 GetMapTileCountH();
	int	 GetTileWidth();
	int	 GetTileHeight();	
	void SetMapTileCountW(int width);						// Set How many tiles in a row
	void SetMapTileCountH(int height);
	void SetTileWidth(int width);
	void SetTileHeight(int height);

	/* Layer information */
	int  GetLayerCount();
	void SetLayerCount(int layerCount);
	void AddLayer(std::vector<int>* data, int width, int height, std::string name, std::string type, 
						bool visible, int x, int y);		// Add a new layer, call the build layer method inside

	/* Tileset information */
	int  GetTilesetCount();
	void SetTilesetCount(int tilesetCount);
	void AddTileset(std::string image, std::string name, int firstGrid, int imageWidth,
					int imageHeight, int tileWidth, int tileHeight);		// Add a new tileset, call the build tileset method inside
	void DrawMap(int cameraPosX, int cameraPosY);
private:
	bool BuildMapSurface(int cameraPosX, int cameraPosY);

	SLayer* BuildLayer(std::vector<int>* data, int width, int height, std::string name, std::string type, 
						bool visible, int x, int y);		// Build a layer based on the information passed in
	void DestroyLayer(SLayer* layer);
	STileSet* BuildTileset(std::string image, std::string name, int firstGrid, int imageWidth,
					int imageHeight, int tileWidth, int tileHeight);		// Build a tileset based on the information passed in
	void DestroyTileset(STileSet* tileset);

	/*Draw Map related*/
	void ChangeViewToMapCoord(int& x, int& y);
private:
	IDirect3DDevice9*			m_ipDevice;
	/* Map basic information */
	SRectWH						m_sMapWH;					// Hold the value of w/h of the map in tile.
	SRectWH						m_sTileWH;					// Hold the value of w/h of the tile 

	/* Map layer information */
	int							m_iLayerCount;				// Hold the number of map layers
	std::vector<SLayer*>*		m_pvspLayer;				// Hold all layer information into this vector of pointer of layers

	/* Map tileset information */
	int							m_iTilesetCount;			// Get the number of tileset needed in the map
	std::vector<STileSet*>*		m_pvspTileSet;				// Hold the tileset source information

	CTile*						m_pTiles;					// Hold all tiles need in the map

	/*Draw the background associated*/
	IDirect3DSurface9*			m_ipMapSurface;				// Background map surface, copy the tile texture into this surface and then swap with the rander target suface
};