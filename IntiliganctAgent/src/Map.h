#pragma once

#include <vector>
#include <string>
#include <d3d9.h>
#include <sstream>
#include "WinConfigure.h"
#include "Tile.h"
#include "Texture.h"
// What does the map need?
// 1: how many layers?
// 2: what's the w/h of each layer?
// 3: how many tiles?
// 4: what's the w/h of each tile?
// 5: what's the path of each tile, so that I can load it into the memory?
// 6: how to rearrange the tiles or what's the tile position?

class CMap {
public:
	CMap();
	~CMap();

	/**
	 * A normal map consists of many layers, like background, foreground, top etc.
	 * Structure map_layer holds the information of each layer
	 */
	struct map_layer {
		std::vector<int>		data;														// 2D vector store the layer index information of tiles
		int						width;														// layer width
		int						height;														// layer height
		std::string				name;														// layer name
		std::string				type;														// layer type, like 'tile layer' or 'object layer'
		bool					visible;													// layer is visible or not
		int						x;															// start position of layer, x
		int						y;															// start position of layer, y
	};
	/**
	 * A tile set is an image which can be divided in to several parts, each part is 
	 * a tile.
	 */
	struct map_tilestet {
		int						firstGrid;													// start index of the tile in this image
		std::wstring			image;														// relative path of the image
		std::string				name;														// image name
		int 					img_width;													// image width
		int						img_height;													// image height
		int						margin;														// 
		int						spacing;													// 
		int						tile_width;													// tile width
		int						tile_height;												// tile height
	};

	bool						LoadMap(IDirect3DDevice9* ipDevice, 
											std::wstring wstrFilePath);

	/**
	 * Map basic information
	 */
	int							GetTileCountRow();											// tile count in row
	int							GetTileCountColumn();										// tile count in column							
	int							GetTileWidth();												// basic tile width
	int							GetTileHeight();											// basic tile height
	void						SetTileCountRow(int width);									// set tile count in row
	void						SetTileCountColumn(int height);								// set tile count in column
	void						SetTileWidth(int width);									// set tile basic tile width
	void						SetTileHeight(int height);									// set tile basic tile height

	/* Layer information */
	int							GetLayerCount();
	void						AddLayer(map_layer* player);								// Add a new layer, call the build layer method inside

	/* Tileset information */
	int							GetTilesetCount();
	void						AddTileset(map_tilestet* ptileset);							// Add a new tile set, call the build tile set method inside
	
	void						DrawMap(int cameraPosX, int cameraPosY);

	bool						BuildTiles();
private:

	bool						BuildMapSurface(int cameraPosX, int cameraPosY);

	/*Draw Map related*/
	void						ChangeViewToMapCoord(int& x, int& y);
private:
	IDirect3DDevice9*			m_ipDevice;
	IDirect3DSurface9*			m_ipMapSurface;												// Background map surface, copy the tile texture into this surface and then swap with the rander target suface

	int							m_iTileCountRow;											// tile count in x direction
	int							m_iTileCountColumn;											// tile count in y direction

	int							m_iTileWidth;												// tile width 
	int							m_iTileHeight;												// tile height

	std::vector<map_layer*>		m_pvLayer;													// layer information, get count of layers directly.

	std::vector<map_tilestet*>	m_pvTileSet;												// tileset information

	std::vector<CTile*>			m_pvTiles;													// all tiles need in the map
};