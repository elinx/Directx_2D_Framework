#include "Map.h"
#include "JsonParser.h"

CMap::CMap()
{
	m_pvspLayer = new std::vector<SLayer*>;
	m_pvspTileSet = new std::vector<STileSet*>;
}

CMap::~CMap()
{
	for(std::vector<SLayer*>::iterator iter = m_pvspLayer->begin();
		iter != m_pvspLayer->end(); ++ iter)
		this->DestroyLayer(*iter);// ?

	for(std::vector<STileSet*>::iterator iter = m_pvspTileSet->begin();
		iter != m_pvspTileSet->end(); ++ iter) 
		this->DestroyTileset(*iter);

	delete m_pvspLayer;
	delete m_pvspTileSet;
}

bool CMap::LoadMap(std::wstring wstrFilePath)
{
	CJsonParser jparser;

	jparser.ReadFromFile(wstrFilePath, this);		// Load all information needed into the map object.

	return true;
}
// Get How many tiles in a row
int	 CMap::GetMapTileCountW()								
{
	return m_sMapWH.width;
}
// Get How many tiles in a column
int	 CMap::GetMapTileCountH()
{
	return m_sMapWH.height;
}
// Get tile width
int	 CMap::GetTileWidth()
{
	return m_sTileWH.width;
}
// Get tile height
int	 CMap::GetTileHeight()
{
	return m_sTileWH.height;
}
// Set How many tiles in a row
void CMap::SetMapTileCountW(int width)						
{
	m_sMapWH.width = width;
}
// Set How many tiles in a column
void CMap::SetMapTileCountH(int height)
{
	m_sMapWH.height = height;
}
// Set tile width
void CMap::SetTileWidth(int width)
{
	m_sTileWH.width = width;
}
// Set tile height
void CMap::SetTileHeight(int height)
{
	m_sTileWH.height = height;
}
/* Layer information */
int  CMap::GetLayerCount()
{
	return m_iLayerCount;
}
void CMap::SetLayerCount(int layerCount)
{
	m_iLayerCount = layerCount;
}
// Add a new layer, call the build layer method inside
void CMap::AddLayer(std::vector<int>* data, int width, int height, std::string name, std::string type, 
					bool visible, int x, int y)		
{
	m_pvspLayer->push_back( this->BuildLayer(data, width, height, name, type, visible, x, y) );
}
// Build a layer based on the information passed in
CMap::SLayer* CMap::BuildLayer(std::vector<int>* data, int width, int height, std::string name, std::string type, 
					bool visible, int x, int y)		
{
	SLayer* layer			= new SLayer;	// new a layer on heap
	layer->data				= data;
	layer->layerWH.width	= width;
	layer->layerWH.height	= height;
	layer->name				= name;
	layer->type				= type;
	layer->visible			= visible;
	layer->x				= x;
	layer->y				= y;

	return layer;
}
// Delete the layer malloc on the heap
void CMap::DestroyLayer(SLayer* layer)
{
	// Delete the index data
	delete layer->data;
	layer->data = NULL;

	// Delete the layer
	delete layer;
	layer = NULL;
}

/* Tileset information */
int  CMap::GetTilesetCount()
{
	return m_iTilesetCount;
}
void CMap::SetTilesetCount(int tilesetCount)
{
	m_iTilesetCount = tilesetCount;
}
// Add a new layer, call the build layer method inside
void CMap::AddTileset(std::string image, std::string name, int firstGrid, int imageWidth,
					int imageHeight, int tileWidth, int tileHeight)		
{
	m_pvspTileSet->push_back( this->BuildTileset(image, name, firstGrid, imageWidth, imageHeight, tileWidth, tileHeight) );
}
// Build a layer based on the information passed in
CMap::STileSet* CMap::BuildTileset(std::string image, std::string name, int firstGrid, int imageWidth,
					int imageHeight, int tileWidth, int tileHeight)		
{
	STileSet* tileset			= new STileSet;	// new a layer on heap
	tileset->image				= image;
	tileset->imageWH.width		= tileWidth;
	tileset->imageWH.height		= imageHeight;
	tileset->name				= name;
	tileset->tileWH.width		= tileWidth;
	tileset->tileWH.height		= tileHeight;
	tileset->firstGrid			= firstGrid;

	return tileset;
}
// Delete the layer malloc on the heap
void CMap::DestroyTileset(STileSet* tileset)
{
	// Delete the tileset
	delete tileset;
	tileset = NULL;
}