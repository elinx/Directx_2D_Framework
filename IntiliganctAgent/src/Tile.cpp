#include "Tile.h"

CTile::CTile()
	:
	m_TexturesCount(0),
	m_viWidths(NULL),			
	m_viHeights(NULL),		
	m_viColumns(NULL),		
	m_viFirstGridNum(NULL),	
	m_vpTilesetTexture(NULL)
{

}

CTile::~CTile()
{
	Free();
}
bool CTile::Create(IDirect3DDevice9* ipDevice, int TexturesCount)
{
	assert(ipDevice != NULL);

	m_ipDevice = ipDevice;
	m_TexturesCount = TexturesCount;

    m_viWidths			= new std::vector<int>(TexturesCount);
    m_viHeights			= new std::vector<int>(TexturesCount);
    m_viColumns			= new std::vector<int>(TexturesCount);
	m_viFirstGridNum	= new std::vector<int>(TexturesCount);

	// New space for textures
	m_vpTilesetTexture  = new std::vector<CTexture*>(TexturesCount);		// Space for vector
	for(std::vector<CTexture*>::iterator iter = m_vpTilesetTexture->begin();
			iter != m_vpTilesetTexture->end();
			++iter)
	{
		//m_vpTilesetTexture->push_back(new CTexture());						// Space for textures
		*iter = new CTexture();
	}
	return true;
}
bool CTile::Free()
{	
	for(std::vector<CTexture*>::iterator iter = m_vpTilesetTexture->begin();
			iter != m_vpTilesetTexture->end();
			++iter)
	{
		delete *iter;														// Delete textures first
	}
	delete m_vpTilesetTexture;												// Delete the vector
	delete m_viWidths;			
	delete m_viHeights;		
	delete m_viColumns;		
	delete m_viFirstGridNum;	
	return true;
}
bool CTile::Load(int TextureIndex, std::wstring wstrFilename,
			int imageWidth, int imageHeight,
            int tileWidth, int tileHeight,
            D3DCOLOR Transparent,
            D3DFORMAT Format)
{
	(*m_vpTilesetTexture)[TextureIndex]->LoadFromFile(m_ipDevice, wstrFilename,imageWidth, imageHeight, Transparent, Format);
	(*m_viWidths)[TextureIndex] = tileWidth;
	(*m_viHeights)[TextureIndex] = tileHeight;
	(*m_viColumns)[TextureIndex] = (*m_vpTilesetTexture)[TextureIndex]->GetWidth() / (*m_viWidths)[TextureIndex];
	return true;
}
bool CTile::Free(int TextureIndex)
{
	(*m_vpTilesetTexture)[TextureIndex]->Free();
	return true;
}

int CTile::GetWidth(int TextureIndex)
{
  // Error checking
  if(TextureIndex >= m_TexturesCount || m_viWidths == NULL)
   return 0;

  return (*m_viWidths)[TextureIndex];
}

int CTile::GetHeight(int TextureIndex)
{
  // Error checking
  if(TextureIndex >= m_TexturesCount || m_viHeights == NULL)
   return 0;

  return (*m_viHeights)[TextureIndex];
}

int CTile::GetCount(int TextureIndex)
{
  // Error checking
  if(TextureIndex >= m_TexturesCount || m_vpTilesetTexture == NULL ||
     m_viColumns == NULL || m_viWidths == NULL || m_viHeights == NULL)
   return 0;

  return (*m_viColumns)[TextureIndex] + (*m_vpTilesetTexture)[TextureIndex]->GetHeight() / (*m_viHeights)[TextureIndex];
}
bool CTile::Draw(int TextureIndex, int TileIndex,                 
            int ScreenX, int ScreenY,                    
            D3DCOLOR Color,                   
            float XScale, float YScale)
{
	return true;	
}
// Passed in a tileIndex number and return the 
// Number of which texture the tile is in.
int CTile::FindTextureByTileIndex(int tileIndex)
{
	// Should optimized!!
	for(unsigned int index = 0; index < m_viFirstGridNum->size(); ++index)
	{
		if((*m_viFirstGridNum)[index] = tileIndex)
			return index;
		else if(((*m_viFirstGridNum)[index] > tileIndex) && (index != 0))
			return (index - 1);
		else if(((*m_viFirstGridNum)[index] < tileIndex) && (index = m_viFirstGridNum->size()))
			return index;
	}
	return -1;				// If can't find the tile index 
}
void CTile::BuildTileAt(int tileIndex, IDirect3DSurface9* m_ipMapSruface, int mapX, int mapY)
{
	int textureIndex = this->FindTextureByTileIndex(tileIndex);
	assert(textureIndex >=0 && textureIndex < m_TexturesCount);
	
	(*m_vpTilesetTexture)[textureIndex]->BuildTileAt(tileIndex - (*m_viFirstGridNum)[textureIndex], (*m_viWidths)[textureIndex],
		(*m_viHeights)[textureIndex],m_ipMapSruface, mapX, mapY);
}