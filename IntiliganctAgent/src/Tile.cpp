#include "Tile.h"

/**
 * Description: Default Constructor
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
CTile::CTile()
	:
m_ipDevice(NULL),
m_pTexture(new CTexture)
m_width(0),
m_height(0),
m_ID(0)
{

}
/**
 * Description: Constructor
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
CTile::CTile(IDirect3DDevice9* ipDevice, 
				unsigned int id,
				unsigned int w,
				unsigned int h)
	:
m_ipDevice(ipDevice),
m_pTexture(new CTexture(ipDevice, w, h))
m_width(w),
m_height(h),
m_ID(id)
{}
/**
 * Description: Copy Constructor
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
CTile::CTile(const CTile& tile)
{
	m_ipDevice					= tile.m_ipDevice;											// shallow copy
	
	m_width						= tile.m_width;
	m_height					= tile.m_height;
	m_ID						= tile.m_ID;

	CTexture *ptex				= new CTexture(*tile.m_pTexture);							// deep copy
	m_pTexture = ptex;
}
/**
 * Description: Assignment operator
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
CTile& CTile::operator =(const CTile& rhs)
{
	if(*this == rhs)																		// same object
		return *this;

	m_ipDevice					= rhs.m_ipDevice;											// shallow copy
								  
	m_width						= rhs.m_width;
	m_height					= rhs.m_height;
	m_ID						= rhs.m_ID;

	CTexture *ptex				= new CTexture(*rhs.m_pTexture);							// deep copy
	m_pTexture = ptex;

	return *this
}
/**
 * Description: Destructor
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
CTile::~CTile()
{
	delete m_pTexture;
}
/**
 * Description: equal operator
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
bool CTile::operator ==(const CTile& rhs)
{
	return m_ID == rhs.m_ID;
}
/**
 * Description: not equal operator
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
bool CTile::operator !=(const CTile& rhs)
{
	return m_ID != rhs.m_ID;
}
/**
 * Description: Load tiles, the whole image is a tile
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
HRESULT CTile::LoadTile(std::wstring filePath)
{
	assert(m_pTexture != NULL);
	if(FAILED(m_pTexture->LoadTexture(filePath, m_width, m_height))
		return E_FAIL;
	return D3D_OK;
}
/**
 * Description: Load tile, the image contains several tiles, load one specified
 * Parameter: x : x start offset of the image
			  y : y start offset of the image
 * Return Value: 
 * Date: 2014-5-11
 */
HRESULT CTile::LoadTile(std::wstring filePath, int xoffset, int yoffset)
{
	assert(m_pTexture != NULL);
	if(FAILED(m_pTexture->LoadTexture(filePath, x, y, m_width, m_height))
		return E_FAIL;
	return D3D_OK;
}
/**
 * Description: the texture is the new texture
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
HRESULT CTile::LoadTile(CTexture& texture)
{
	assert(m_pTexture != NULL);
	*m_pTexture = texture;																	// deep copy
	return D3D_OK;
}
/**
 * Description: Draw the texture on the screen
 * Parameter: 
 * Return Value: 
 * Date: 2014-5-11
 */
HRESULT CTile::Draw(int x, 
					int y, 
					D3DCOLOR Color,
					float XScale, 
					float YScale)
{
	CSprite* sprite = new CSprite(m_ipDevice);

	sprite->LoadSprite();

	sprite->Draw();

	delete sprite;

	return D3D_OK;
}
// bool CTile::Create(IDirect3DDevice9* ipDevice, int TexturesCount)
// {
// 	assert(ipDevice != NULL);
// 
// 	m_ipDevice = ipDevice;
// 	m_TexturesCount = TexturesCount;
// 
//     m_viWidths			= new std::vector<int>(TexturesCount);
//     m_viHeights			= new std::vector<int>(TexturesCount);
//     m_viColumns			= new std::vector<int>(TexturesCount);
// 	m_viFirstGridNum	= new std::vector<int>(TexturesCount);
// 
// 	// New space for textures
// 	m_vpTilesetTexture  = new std::vector<CTexture*>(TexturesCount);		// Space for vector
// 	for(std::vector<CTexture*>::iterator iter = m_vpTilesetTexture->begin();
// 			iter != m_vpTilesetTexture->end();
// 			++iter)
// 	{
// 		//m_vpTilesetTexture->push_back(new CTexture());						// Space for textures
// 		*iter = new CTexture();
// 	}
// 	return true;
// }
// bool CTile::Free()
// {	
// 	for(std::vector<CTexture*>::iterator iter = m_vpTilesetTexture->begin();
// 			iter != m_vpTilesetTexture->end();
// 			++iter)
// 	{
// 		delete *iter;														// Delete textures first
// 	}
// 	delete m_vpTilesetTexture;												// Delete the vector
// 	delete m_viWidths;			
// 	delete m_viHeights;		
// 	delete m_viColumns;		
// 	delete m_viFirstGridNum;	
// 	return true;
// }
// bool CTile::Load(int TextureIndex, std::wstring wstrFilename,int firstGrid,
// 			int imageWidth, int imageHeight,
//             int tileWidth, int tileHeight,
//             D3DCOLOR Transparent,
//             D3DFORMAT Format)
// {
// 	(*m_vpTilesetTexture)[TextureIndex]->LoadFromFile(m_ipDevice, wstrFilename,imageWidth, imageHeight, Transparent, Format);
// 	(*m_viWidths)[TextureIndex] = tileWidth;
// 	(*m_viHeights)[TextureIndex] = tileHeight;
// 	(*m_viColumns)[TextureIndex] = (*m_vpTilesetTexture)[TextureIndex]->GetWidth() / (*m_viWidths)[TextureIndex];
// 	(*m_viFirstGridNum)[TextureIndex] = firstGrid;
// 	return true;
// }
// bool CTile::Free(int TextureIndex)
// {
// 	(*m_vpTilesetTexture)[TextureIndex]->Free();
// 	return true;
// }
// 
// int CTile::GetWidth(int TextureIndex)
// {
//   // Error checking
//   if(TextureIndex >= m_TexturesCount || m_viWidths == NULL)
//    return 0;
// 
//   return (*m_viWidths)[TextureIndex];
// }
// 
// int CTile::GetHeight(int TextureIndex)
// {
//   // Error checking
//   if(TextureIndex >= m_TexturesCount || m_viHeights == NULL)
//    return 0;
// 
//   return (*m_viHeights)[TextureIndex];
// }
// 
// int CTile::GetCount(int TextureIndex)
// {
//   // Error checking
//   if(TextureIndex >= m_TexturesCount || m_vpTilesetTexture == NULL ||
//      m_viColumns == NULL || m_viWidths == NULL || m_viHeights == NULL)
//    return 0;
// 
//   return (*m_viColumns)[TextureIndex] + (*m_vpTilesetTexture)[TextureIndex]->GetHeight() / (*m_viHeights)[TextureIndex];
// }
// bool CTile::Draw(int TextureIndex, int TileIndex,                 
//             int ScreenX, int ScreenY,                    
//             D3DCOLOR Color,                   
//             float XScale, float YScale)
// {
// 	return true;	
// }
// // Passed in a tileIndex number and return the 
// // Number of which texture the tile is in.
// int CTile::FindTextureByTileIndex(int tileIndex)
// {
// 	// Should optimized!!
// 	for(unsigned int index = 0; index < m_viFirstGridNum->size(); ++index)
// 	{
// 		if((*m_viFirstGridNum)[index] == tileIndex)
// 			return index;
// 		else if(((*m_viFirstGridNum)[index] > tileIndex) && (index != 0))
// 			return (index - 1);
// 		else if(((*m_viFirstGridNum)[index] < tileIndex) && (index == m_viFirstGridNum->size()))
// 			return index;
// 	}
// 	return -1;				// If can't find the tile index 
// }
// /*
//  * 建立贴片地图，这里的tileIndex应该是从0~#，但是0表示没有贴片，所以，当遇到0时，直接跳出即可
//  */
// void CTile::BuildTileAt(int tileIndex, IDirect3DSurface9* m_ipMapSruface, int mapX, int mapY)
// {
// 	if(tileIndex == 0) return;
// 	int textureIndex = this->FindTextureByTileIndex(tileIndex);
// 	assert(textureIndex >=0 && textureIndex < m_TexturesCount);
// 	
// 	(*m_vpTilesetTexture)[textureIndex]->BuildTileAt(tileIndex - (*m_viFirstGridNum)[textureIndex], (*m_viWidths)[textureIndex],
// 		(*m_viHeights)[textureIndex],m_ipMapSruface, mapX, mapY);
// }