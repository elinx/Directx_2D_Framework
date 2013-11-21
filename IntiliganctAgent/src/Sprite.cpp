#include "Sprite.h"

CSprite::CSprite(IDirect3DDevice9* ipDevice, std::wstring filePath, int width, int height)
	:
m_ipDevice(ipDevice),
m_filePath(filePath)
{
	m_ipTexture = NULL;
	HRESULT hr;

	m_iWidth = width;
	m_iHeight = height;

	if(FAILED(hr = D3DXCreateTextureFromFileEx(m_ipDevice, filePath.c_str(), width, height,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 255, 255), 
		NULL, NULL,&m_ipTexture)))
			assert(false);// create and load the bitmap.
	D3DXCreateSprite(m_ipDevice, &m_ipSprite);
}
CSprite::~CSprite()
{
	if (m_ipTexture != NULL)
	{
		m_ipTexture->Release();
		m_ipTexture = NULL;
	}
	if (m_ipSprite != NULL)
	{
		m_ipSprite->Release();
		m_ipSprite = NULL;
	}
}
void CSprite::DrawBitmap(D3DXVECTOR3* pos, D3DCOLOR mask, bool reverse)
{
	assert(m_ipSprite /*!= NULL*/);
	//boost::mutex::scoped_lock lock(gGraphic_Mutex);

	m_ipSprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	// flip the sprite horizontally
	D3DXMATRIX oldMat;
	m_ipSprite->GetTransform(&oldMat);
	if(reverse)
	{
		D3DXMATRIX mat;
		D3DXVECTOR2 scale( -1.0f, 1.0f );		// flip horizon
		D3DXVECTOR2 center(pos->x, pos->y);		// set flip center(upper left corner of the sprite)
		D3DXVECTOR2 translate(float(m_iWidth), 0);

		D3DXMatrixTransformation2D(&mat, &center, NULL, &scale, NULL, NULL, &translate);
		m_ipSprite->SetTransform(&mat);
	}
	m_ipSprite->Draw(m_ipTexture, NULL, NULL, pos, mask);
	m_ipSprite->SetTransform(&oldMat);
	m_ipSprite->End();

}