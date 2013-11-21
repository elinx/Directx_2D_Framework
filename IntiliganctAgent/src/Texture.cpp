#include "Texture.h"
#include <fstream>
extern std::ofstream fcout;

CTexture::CTexture() 
	:
  m_ipDevice(NULL),
  m_Texture(NULL),
  m_Width(0),
  m_Height(0)
{
}

CTexture::~CTexture()
{
	Free();
}

bool CTexture::LoadFromFile(IDirect3DDevice9* ipDevice, std::wstring wstrFilename,
						int textureWidth, int textureHeight,
						DWORD Transparent, D3DFORMAT Format)
{
	//Free();
	assert((ipDevice != NULL) && (wstrFilename.c_str() != NULL));// Not so good way....
	m_ipDevice = ipDevice;
	HRESULT hr;
	//if(FAILED(D3DXCreateTextureFromFileEx(ipDevice,
	//	wstrFilename.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT,
	//	0, Format, D3DPOOL_MANAGED, 
	//	D3DX_DEFAULT, D3DX_DEFAULT,
	//	Transparent, NULL, NULL, &m_Texture)))
	//		return false;
	if(FAILED(hr = D3DXCreateTextureFromFileEx(ipDevice, wstrFilename.c_str(), textureWidth, textureHeight,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, 
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 255, 255), 
		NULL, NULL,&m_Texture)))
	{
		if(hr == D3DERR_INVALIDCALL)
			return false;
		if(hr == D3DERR_NOTAVAILABLE)
			return false;
		if(hr == D3DERR_OUTOFVIDEOMEMORY)
			return false;
		if(hr == D3DXERR_INVALIDDATA)
			return false;
		if(hr == E_OUTOFMEMORY)
			return false;
		return false;
	}
	m_Width = GetWidth();
	m_Height = GetHeight();

	return true;
}

bool CTexture::LoadFromTexture(IDirect3DDevice9* ipDevice, IDirect3DTexture9 *Texture)
{
	D3DLOCKED_RECT SrcRect, DestRect;
	D3DSURFACE_DESC Desc;

	Free();

	assert((ipDevice != NULL) && (Texture != NULL));
	m_ipDevice = ipDevice;
    
	// Copy texture over from the Texture passed in to this texture
	Texture->GetLevelDesc(0, &Desc);
	m_Width  = Desc.Width;
	m_Height = Desc.Height;
	ipDevice->CreateTexture(m_Width, m_Height, 0, 0, Desc.Format, D3DPOOL_MANAGED, &m_Texture, NULL);
	
	Texture->LockRect(0, &SrcRect, NULL, D3DLOCK_READONLY);
	m_Texture->LockRect(0, &DestRect, NULL, 0);

	memcpy(DestRect.pBits, SrcRect.pBits, SrcRect.Pitch * m_Height);

	m_Texture->UnlockRect(0);
	Texture->UnlockRect(0);

	return true;
}

bool CTexture::Free()
{
	m_Texture->Release();
	m_Texture = NULL;

	m_Width = m_Height = 0;

	return TRUE;
}

bool CTexture::IsLoaded()
{
	if(m_Texture == NULL)
		return false;
	return true;
}

IDirect3DTexture9 *CTexture::GetTexture()
{
	return m_Texture;
}

int CTexture::GetWidth()
{
  D3DSURFACE_DESC d3dsd;

  if(m_Texture == NULL)
    return 0;

  if(FAILED(m_Texture->GetLevelDesc(0, &d3dsd)))
    return 0;

  return d3dsd.Width;
}

int CTexture::GetHeight()
{
  D3DSURFACE_DESC d3dsd;

  if(m_Texture == NULL)
    return 0;

  if(FAILED(m_Texture->GetLevelDesc(0, &d3dsd)))
    return 0;

  return d3dsd.Height;
}

D3DFORMAT CTexture::GetFormat()
{
  D3DSURFACE_DESC d3dsd;

  if(m_Texture == NULL)
    return D3DFMT_UNKNOWN;

  if(FAILED(m_Texture->GetLevelDesc(0, &d3dsd)))
    return D3DFMT_UNKNOWN;

  return d3dsd.Format;
}

bool CTexture::Draw(long DestX, long DestY,                  
                    long SrcX, long SrcY,                    
                    long Width, long Height,                 
                    float XScale, float YScale,              
                    D3DCOLOR Color)
{
//RECT Rect;
//ID3DXSprite *pSprite;
//
//if(m_Texture == NULL)
//  return FALSE;
//if(m_Graphics == NULL)
//  return FALSE;
//if((pSprite = m_Graphics->GetSpriteCOM()) == NULL)
//  return FALSE;
//
//if(!Width)
//  Width = m_Width;
//if(!Height)
//  Height = m_Height;
//
//Rect.left = SrcX;
//Rect.top  = SrcY;
//Rect.right = Rect.left + Width;
//Rect.bottom = Rect.top + Height;
//
//if(FAILED(pSprite->Draw(m_Texture,                          \
//       &Rect, &D3DXVECTOR2(XScale, YScale),                 \
//       NULL, 0.0f,                                          \
//       &D3DXVECTOR2((float)DestX, (float)DestY),            \
//       Color)))
//  return FALSE;
  return TRUE;
}
void CTexture::GetTileCoordOnTexture(int tileIndex,int tileWidth,int tileHeight, int& tileTextureX, int& tileTextureY)
{
	tileTextureX = (tileIndex % (m_Width / tileWidth)) * tileWidth;
	tileTextureY = (tileIndex / (m_Width / tileWidth)) * tileHeight;
}
inline D3DCOLOR AlphaBlending(D3DCOLOR dColor, D3DCOLOR sColor)
{
	// the base element of source pixel
	//unsigned char da = dColor >> 24;
	//unsigned char dr = (dColor & 0x00ff0000) >> 16;
	//unsigned char dg = (dColor & 0x0000ff00) >> 8;
	//unsigned char db = dColor & 0x000000ff;
	//
	//unsigned char sa = sColor >> 24;
	//unsigned char sr = (sColor & 0x00ff0000) >> 16;
	//unsigned char sg = (sColor & 0x0000ff00) >> 8;
	//unsigned char sb = sColor & 0x000000ff;
	//
	//// the result element of the result pixel
	//unsigned char ra = sa;
	//unsigned char rr = ( sr - dr)* ra / 255 + dr;
	//unsigned char rg = ( sg - dg)* ra / 255 + dg;
	//unsigned char rb = ( sb - db)* ra / 255 + db;
	//									
	//return D3DCOLOR_ARGB(ra, rr, rg, rb);
	
	//return (sColor==0) ? dColor : sColor;
	//return sColor;
}
/*
 * ½¨Á¢ÌùÆ¬µØÍ¼
 */
void CTexture::BuildTileAt(int tileIndex, int tileWidth,int tileHeight, 
		IDirect3DSurface9* m_ipMapSurface, int mapX, int mapY)
{
	int tileTextureX, tileTextureY;
	GetTileCoordOnTexture(tileIndex, tileWidth, tileHeight,tileTextureX, tileTextureY);
	// Here is the main part, the core.
	IDirect3DSurface9* tempTextureSurface;
	if(FAILED(m_Texture->GetSurfaceLevel(0, &tempTextureSurface)))
		MessageBox(0, L"ERROR", L"Get texture surface error", MB_OK);// get the surface of the texture
	// Get the description structure of the temp surface for debug
	D3DSURFACE_DESC			tempSurfaceDesc;
	tempTextureSurface->GetDesc(&tempSurfaceDesc);

	RECT dRect = {mapX, mapY, mapX + tileWidth, mapY + tileHeight};
	RECT sRect = {tileTextureX, tileTextureY, tileTextureX + tileWidth, tileTextureY + tileHeight};
	//POINT point = {tileTextureX, tileTextureY};
	
	D3DLOCKED_RECT textureRect, mapRect;

	//Lock the texture surface and read the texture rectangle 
	if((tempTextureSurface->LockRect(&textureRect, &sRect, D3DLOCK_DISCARD | D3DLOCK_NO_DIRTY_UPDATE)) != D3D_OK)
		MessageBox(0, L"ERROR", L"Lock texture rectangel error", MB_OK);
	if((m_ipMapSurface->LockRect(&mapRect, &dRect, D3DLOCK_DISCARD | D3DLOCK_NO_DIRTY_UPDATE)) != D3D_OK)
		MessageBox(0, L"ERROR", L"Lock map rectangel error", MB_OK);

	//Copy textureRect to mapRect, is this ok?!
	//NOTE:the pitch get from the D3DLOCKED_RECT is NOT the pitch of the LOCKED MEM, it is the ORIGINAL PITCH  of the surface
	//CopyMemory(mapRect.pBits, textureRect.pBits, 32 * 4);// height is 32 for simplicity
	DWORD* dRectPtr = (DWORD*)mapRect.pBits;
	DWORD* sRectPtr = (DWORD*)textureRect.pBits;
	for(int index = 0; index < tileHeight; ++index)
	{
		/*Flaw: the layer objects on the front not transparent! 23bps*/
		//CopyMemory(dRectPtr, sRectPtr, tileWidth << 2);// COPY A LINE, 4 byes of one pixel
		/*Try alpha blending, but may become too slow, just hava a try 23bps--->22bps now*/
		for(int w = 0; w < tileWidth; ++w)
		{
			//*(dRectPtr + w) = AlphaBlending(*(dRectPtr + w), *(sRectPtr + w));
			//*(dRectPtr + w)= *(sRectPtr + w);
			*(dRectPtr + w) = *(sRectPtr + w) ? *(sRectPtr + w) : *(dRectPtr + w);
		}
		dRectPtr += mapRect.Pitch >> 2 ;
		sRectPtr += textureRect.Pitch >> 2 ;
	}

	//MessageBox(0, L"ERROR", L"Copy rectangel error", MB_OK);

	m_ipMapSurface->UnlockRect();
	tempTextureSurface->UnlockRect();
	// Source surface must be created on the default memory pool
	//if(FAILED(m_ipDevice->StretchRect(tempTextureSurface, &sRect, m_ipMapSurface, &dRect, D3DTEXF_NONE)))
		//MessageBox(0, L"ERROR", L"Copy texture error", MB_OK);

	//RECT sRect = { tileTextureX, tileTextureY, tileTextureX + tileWidth, tileTextureY + tileHeight };
	//POINT dPoint = { mapX, mapY};

	//fcout << "Map position x: " << mapX << '\t' << "y: " << mapY << std::endl;

	// The sorce surface of CopyRects function must be malloced on the default memory not on the main mem.
	//if(FAILED(m_ipDevice->UpdateSurface(tempTextureSurface, &sRect, m_ipMapSurface, &dPoint)))
		//MessageBox(0, L"ERROR", L"Copy texture error", MB_OK);
	//CopyRects(tempTextureSurface, &sRect, m_ipMapSurface, &dRect);

	tempTextureSurface->Release();
	tempTextureSurface = NULL;
}