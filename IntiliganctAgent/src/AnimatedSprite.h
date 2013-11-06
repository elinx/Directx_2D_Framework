#pragma once
#include <assert.h>
#include "Sprite.h"

class CAnimatedSprite
{
public:
	CAnimatedSprite(IDirect3DDevice9* ipDevice)
	: 
	m_spritesNum(0),
	m_curSpriteFrameIndex(0),
	m_startRuning(false),
	m_ipDevice(ipDevice)
	{
		m_pSprite = new CSprite*;
	}

	~CAnimatedSprite()
	{
		if(!m_pSprite)
			for (unsigned int index = 0; index < m_spritesNum; ++index)
			{
				if ((*m_pSprite != NULL))
				{
					delete	*m_pSprite;
					*m_pSprite = NULL;
				}
			}
	}

	void LoadSprites(std::wstring filePathBase, unsigned int spritesNum, int width, int height)
	{
		for (unsigned int index = 0; index < spritesNum; ++index)
		{
			std::wstringstream		wsstream;
			wsstream << filePathBase << std::setw(2) << std::setfill(wchar_t('0')) << index << L".png";
			std::wstring wstr = wsstream.str();

			//*m_pSprite
			m_pSprite[index] = new CSprite(m_ipDevice, wsstream.str(), width, height);
			assert(m_pSprite[index] != NULL);
		}
	}

	void RunSprite(bool run, int x, int y, int frameIndex, D3DCOLOR mask = D3DCOLOR_ARGB(255, 255, 255, 255))
	{
		if (!run) frameIndex = 0; // if no key or specific key is pressed, do not show the animation but just
								  // show a static picture
		D3DXVECTOR3 pos = D3DXVECTOR3(float(x),  float(y), 0.0f);
		m_pSprite[frameIndex]->DrawBitmap(&pos, mask);
	}
private:
	IDirect3DDevice9*		m_ipDevice;
	bool					m_startRuning;
	unsigned int			m_spritesNum;
	unsigned int			m_curSpriteFrameIndex;
	CSprite**				m_pSprite;
	// TODO: Should also contain the sprite height and width information
};