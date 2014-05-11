#include "Map.h"
#include "JsonParser.h"

CMap::CMap()
{
	m_pTiles = new CTile;
}

CMap::~CMap()
{
	for(std::vector<map_layer*>::iterator iter = m_pvLayer.begin();
		iter != m_pvLayer.end(); ++ iter)
			delete *iter;

	for(std::vector<map_tilestet*>::iterator iter = m_pvTileSet.begin();
		iter != m_pvTileSet.end(); ++ iter) 
			delete *iter;

	delete m_pTiles;
}
// Copy from the internet, maybe not safe!
// std::wstring s2ws(const std::string& s)
// {
//     setlocale(LC_ALL, "chs"); 
//     const char* _Source = s.c_str();
//     size_t _Dsize = s.size() + 1;
//     wchar_t *_Dest = new wchar_t[_Dsize];
//     wmemset(_Dest, 0, _Dsize);
//     mbstowcs(_Dest,_Source,_Dsize);
//     std::wstring result = _Dest;
//     delete []_Dest;
//     setlocale(LC_ALL, "C");
//     return result;
// }
/**
 * Description: store all tiles needed into the vector
 * Process Flow: 1. loop through the tile set, create a texture of the specific tile set image
				 2. assign the specific part of the texture to the tile according to the grid id
				 3. create a new tile and save the pointer into the tile vector
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-9
 */
bool CMap::BuildTiles()
{
	HRESULT hr;

	for (int i = 0; i < m_pvTileSet.size(); ++i)
	{
		std::wstringstream wsstream;
		CTexture texture;

		wsstream << L"./Assets/tileset/" << m_pvTileSet[index]->image);
		
		if (!texture.LoadFromFile(m_ipDevice,
			wsstream.str(),
			m_pvTileSet[index]->img_width,
			m_pvTileSet[index]->img_height))
		{
			MessageBoxA(NULL, "Create tile set texture error", "Error", MB_OK);
			return false;
		}
	}
	m_pTiles->Create(ipdevice, m_iTilesetCount);	// Specific how many texture to create
	for(int index = 0; index < m_iTilesetCount; ++index)
	{
		std::wstringstream wsstream;
		wsstream << L"./Assets/tileset/" << s2ws((*m_pvspTileSet)[index]->image);
		m_pTiles->Load(index, wsstream.str(), (*m_pvspTileSet)[index]->firstGrid,
			(*m_pvspTileSet)[index]->imageWH.width, 
			(*m_pvspTileSet)[index]->imageWH.height, 
			(*m_pvspTileSet)[index]->tileWH.width,
			(*m_pvspTileSet)[index]->tileWH.height, 
			D3DCOLOR_XRGB(0, 255, 255));
	}
}
/**
 * Description: Load the game map
				1. parse the json format tile map
				2. build the tiles need in this project
				3. create a map surface
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-9
 */
bool CMap::LoadMap(IDirect3DDevice9* ipdevice, std::wstring wstrFilePath)
{
	try 
	{
		CJsonParser jparser;

		jparser.ReadFromFile(wstrFilePath, this);													// parse and get information from json file

		m_ipDevice = ipdevice;
		//m_ipDevice->CreateRenderTarget(800, 600, D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, true, &m_ipMapSurface, NULL);
		
		if(FAILED(m_ipDevice->CreateOffscreenPlainSurface(800,										// create a map surface to draw tiles on
			600,
			D3DFMT_A8R8G8B8, 
			D3DPOOL_SYSTEMMEM, 
			&m_ipMapSurface, 
			NULL)))
		{
			MessageBox(NULL, L"Create map surface error!", L"Error", MB_OK);						// TODO: Use the back buffer instead of the map surface
		}

		BuildTiles();																				// init the tile and texture objects
	}
	catch(std::exception& e) 
	{
		MessageBoxA(0, e.what(), "Load map Error", MB_OK);
		return false;
	}
	return true;
}
// Get How many tiles in a row
int	 CMap::GetTileCountRow()								
{
	return m_iTileCountRow;
}
// Get How many tiles in a column
int	 CMap::GetTileCountColumn()
{
	return m_iTileCountColumn;
}
// Get tile width
int	 CMap::GetTileWidth()
{
	return m_iTileWidth;
}
// Get tile height
int	 CMap::GetTileHeight()
{
	return m_iTileHeight;
}
// Set How many tiles in a row
void CMap::SetTileCountRow(int width)						
{
	m_iTileCountRow = width;
}
// Set How many tiles in a column
void CMap::SetTileCountColumn(int height)
{
	m_iTileCountColumn = height;
}
// Set tile width
void CMap::SetTileWidth(int width)
{
	m_iTileCountRow = width;
}
// Set tile height
void CMap::SetTileHeight(int height)
{
	m_iTileCountColumn = height;
}
/* Layer information */
int  CMap::GetLayerCount()
{
	return m_pvLayer.size();
}

// Add a new layer, call the build layer method inside
void CMap::AddLayer(map_layer* player)		
{
	assert(player != NULL);
	m_pvLayer.push_back(player);
}

/* Tileset information */
int  CMap::GetTilesetCount()
{
	return m_pvTileSet.size();
}

// Add a new layer, call the build layer method inside
void CMap::AddTileset(map_tilestet* ptileset)		
{
	m_pvTileSet.push_back(ptileset);
}

// 这个函数用来生成可视的地图
// 1、用到的参数：MapSurface这个是目标；x, y也就是贴片在地图上的位置；TileIndex，贴片的索引，这个是源；
// 2、思路：通过TileIndex找到贴片的纹理坐标位置和大小，地图上的x，y已经找到；然后只用一个CopyRect函数
//    即可实现把纹理的矩形copy到地图的Surface里边了。
bool CMap::BuildMapSurface(int cameraPosX, int cameraPosY)
{
	// ChangeViewToMapCoord(agentPosX, agentPosY);
	// For simplity, here just use the most simple example: the view's original point
	// Is inditical to the map's originale point
	int tileIndex = 0, baseTileIndex;
	baseTileIndex = cameraPosX / 32 + 100 * (cameraPosY % 32);

	for(int layerIndex = 0; layerIndex < m_pvspLayer->size(); ++layerIndex)
	{
		for(int i = 0; i < WND_HEIGHT / m_sTileWH.height /*+ 1*/; ++i)
		{
			for(int j = 0; j <  WND_WIDTH / m_sTileWH.width; ++j)
			{
				//tileIndex = (j+1) + (i+1) * (WND_WIDTH / m_sTileWH.width);
				//if(tileIndex > 100)
				//	tileIndex = 1;
				tileIndex = baseTileIndex + j + i * 100;
				m_pTiles->BuildTileAt((*(*m_pvspLayer)[layerIndex]->data)[tileIndex], m_ipMapSurface, j * m_sTileWH.width, i * m_sTileWH.height);
			}
		}
	}
	//m_pTiles->BuildTileAt(1, m_ipMapSurface, 0, 0);
	//int count = (*m_pvspLayer)[0]->data->size();
	//for(int index = 0; index < count; ++index)
	//{
	//	int x = index * m_sTileWH.width % WND_WIDTH;
	//	int y = index * m_sTileWH.width / WND_WIDTH * m_sTileWH.height;
	//	m_pTiles->BuildTileAt((*(*m_pvspLayer)[0]->data)[index], m_ipMapSurface, x, y);
	//}
	return true;
}
//获得智能体的坐标x, y这里的坐标是相对view里边的坐标，要通过一定的手段转换成相对于地图的坐标
//void CMap::DrawMap(int agentPosX, int agentPosY)
//{
//	ChangeToMapCoord(agentPosX, agentPosY);		//现在这里的坐标已经是相对地图原点的坐标
//
//	back:
//	GetViewOrigCoord(viewOrigX, viewOrigY, agentPosX, agentPosY);		//通过智能体的位置获得视口的原点坐标
//	tileIndex = GetTileIndexAtCoord(viewOrigX, viewOrigY);//获得某一坐标下的贴片的索引
//	m_pTiles->BuildTileAt(tileIndex, m_ipMapSruface, mapX, mapY)//地图表面的坐标和所需的贴片索引,mapX, mapY初始化为0，0
//	{
//		//内部实现为：
//		tileTexture = CTile::FindTileTextureAt(tileIndex);//通过索引找到纹理
//		tileTexture.GetTileCoordAt(tileIndex, tileTextureX, tileTextureY);//在该纹理上面定位贴片的原点坐标
//		CopyRect(tileTexture, tileTextureX, tileTextuerY, tileWidth, tileHeight, 
//			m_ipSureface, mapX, mapY);//把纹理上指定坐标的矩形拷贝到地图表面上去
//	}
//	viewOrigX += tileW;
//	viewOrigY += tileH;
//	mapX += tileH;
//	mapY += tileH;
//	Repeat and Go back to 'back' label 
//		Until the Whole map is Built fine and nicely~~
//}
void CMap::ChangeViewToMapCoord(int& x, int& y)
{
	// Do not do this any more, do this opration in the camera class.
	// Do nothing until find the way to transform...
}
void CMap::DrawMap(int cameraPosX, int cameraPosY)
{
	IDirect3DSurface9* 		m_pBackBufferSurface;
	// The Debug trick here is get the description structure of each surface,
	// Then compare the two structure, the two surface can replace each other only when...
	// The information members of the two description be exactlly inditical!
	//IDirect3DSurface9* 		testSurface;
	//D3DSURFACE_DESC			backSurfaceDesc, testSurfaceDesc;

	BuildMapSurface(cameraPosX, cameraPosY);

	//if(FAILED(m_ipDevice->CreateOffscreenPlainSurface(800, 600,
	//	D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &testSurface, NULL)))
	//	MessageBox(NULL, L"Create test surface error!", L"Error", MB_OK);
	//testSurface->GetDesc(&testSurfaceDesc);

	// Get the main surface of the system
	if(FAILED(m_ipDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBufferSurface)))
		MessageBox(0, L"ERROR", L"Get backbuffer error", MB_OK);
	// Copy the map surface to replace the main surface, the main surface is the same to back buffer surface.
	if(FAILED(m_ipDevice->UpdateSurface(m_ipMapSurface, NULL, m_pBackBufferSurface, NULL)))// if rect==null, point must be 0,0 or null
		MessageBox(0, L"ERROR", L"Swap map surface error", MB_OK);
	//m_pBackBufferSurface->GetDesc(&backSurfaceDesc);

	m_pBackBufferSurface->Release();
	m_pBackBufferSurface = NULL;
}