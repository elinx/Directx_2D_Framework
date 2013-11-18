#include "Graphics.h"

extern IDirect3DDevice9*		g_ipDevice;

CGraphics::CGraphics()
{

}

CGraphics::CGraphics(HWND hwnd)
	:
	m_hwnd(hwnd),
	m_ipDevice(NULL),
	m_ipDirect(NULL),
	m_pBackBufferSurface(NULL),
	m_pImageSurface(NULL),
	m_pCursorSurface(NULL)
{
	for (int index = 0; index < FONTSNUM ; ++index)
	{
		m_pFont[index] = NULL;
	}
	//for (int index = 0; index < SPRITESNUM; ++ index)
	//{
	//	m_pSprite[index] = NULL;
	//}
}
CGraphics::~CGraphics()
{
	if (m_ipDirect != NULL)
	{
		m_ipDirect->Release();
		m_ipDirect = NULL;
	}

	if (m_ipDevice != NULL)
	{
		m_ipDevice->Release();
		m_ipDirect = NULL;
	}
	if (m_pBackBufferSurface != NULL)
	{
		m_pBackBufferSurface->Release();
		m_pBackBufferSurface = NULL;
	}
	if (m_pImageSurface != NULL)
	{
		m_pImageSurface->Release();
		m_pImageSurface = NULL;
	}
	if (m_pCursorSurface != NULL)
	{
		m_pCursorSurface->Release();
		m_pCursorSurface = NULL;
	}

	DeleteFont();
	DeleteSprite();
}

// create a font based on the parameters passed into this function.
CFont* CGraphics::LoadFont(int height, int width, int weight, bool italic, std::wstring faceName, std::wstring *filePath)
{
	CFont* pFont;
	if(filePath == NULL)
		pFont = new CFont(m_ipDevice, height, width, weight, italic, faceName);
	else
		pFont = new CCustonFont(m_ipDevice, height, width, weight, italic, faceName, *filePath);
	
	return pFont;
}

void CGraphics::DeleteFont()
{
	for (int index = 0; index < FONTSNUM; ++index)
	{
		if (m_pFont[index] != NULL)
		{
			delete m_pFont[index];	
			m_pFont[index] = NULL;
		}
	}

}
int	CGraphics::GraphicsInit()
{
	D3DPRESENT_PARAMETERS	d3d_para;
	ZeroMemory(&d3d_para, sizeof(d3d_para));

	d3d_para.hDeviceWindow					= m_hwnd;
	d3d_para.Windowed						= TRUE;
	d3d_para.SwapEffect						= D3DSWAPEFFECT_FLIP;

	// new added
	d3d_para.BackBufferWidth				= WND_WIDTH;
	d3d_para.BackBufferHeight				= WND_HEIGHT;
	d3d_para.BackBufferCount				= 1;

	d3d_para.BackBufferFormat				= D3DFMT_A8R8G8B8;
	d3d_para.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;
	d3d_para.Flags							= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	if((m_ipDirect = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		MessageBox(m_hwnd, L"Create Direct3d Failure!", L"ERROR", 0);
		return E_FAIL;
	}

	D3DCAPS9	dcaps;
/*	int vp;*/
	m_ipDirect->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &dcaps);
// 	if (dcaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
// 	{
// 		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
// 	}
// 	else
// 		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if(m_ipDirect->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_REF,
		m_hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE,
		&d3d_para,
		&m_ipDevice
		) != D3D_OK)
	{
		MessageBox(m_hwnd, L"Create D3D_Device Failure!", L"ERROR", 0);
		return E_FAIL;
	}
	g_ipDevice = m_ipDevice;
	if (FontInit() != D3D_OK)
	{
		return E_FAIL;
	}
	SpriteInit();

	InitBackgroundSurface();
	InitCursorSurface();
	return D3D_OK;
}
// When a frame begins, call this function to render the background
// and do some initializing job.
void CGraphics::BeginRender()
{
	m_ipDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(100, 200, 30), 0.0f, 0);	//clear the surface
	m_ipDevice->BeginScene();	// begin draw

}
// When a frame finishes, call this function to show the render effect.
void CGraphics::EndRender()
{
	m_ipDevice->EndScene();		// end draw
	m_ipDevice->Present(NULL, NULL, NULL, NULL);	// swap the background buffer to the front buffer and show it.
}

// draw a text string at (x, y) with color as color
void CGraphics::DrawText(const int FONTTYPE, RECT *rect, std::wstring str, D3DCOLOR color)
{
	m_pFont[FONTTYPE]->FontDrawText(rect, str.c_str(), color);
}

CSprite* CGraphics::LoadSprite(std::wstring filePath, int width, int height)
{
	CSprite* pSprite;
	pSprite = new CSprite(m_ipDevice, filePath, width, height);
	
	return pSprite;
}
void CGraphics::DeleteSprite()
{
	//for (int index = 0; index < SPRITESNUM; ++ index)
	//{
	//	if (m_pSprite[index] != NULL)
	//	{		
	//		delete m_pSprite[index];
	//		m_pSprite[index] = NULL;
	//	}
	//}
}
void CGraphics::DrawSprite(const int SPRITE_TYPE, int x, int y, D3DCOLOR mask)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(float(x),  float(y), 0.0f);
	//m_pSprite[SPRITE_TYPE]->DrawBitmap(&pos, mask);
}

int	CGraphics::FontInit()
{
	// Create a header font and store the pointer into the m_pFont[0] positon.
	m_pFont[FONT_NORMALFONT] = LoadFont(NORMAL_FONT_HEIGHT, NORMAL_FONT_WIDTH, 
		NORMAL_FONT_WEIGHT, false, std::wstring(L"ËÎÌå"));
	// Create a header font and store the pointer into the m_pFont[1] positon.
	m_pFont[FONT_HEADERFONT] = LoadFont(HEADER_FONT_HEIGHT, HEADER_FONT_WIDTH, 
		HEADER_FONT_WEIGHT, false, std::wstring(L"Perfect Dark (BRK)"), 
		&std::wstring(L"./Assets/pdark.ttf"));
	// Create a Menu font and store the pointer into the m_pFont[1] positon.
	m_pFont[FONT_MENUFONT] = LoadFont(MENU_FONT_HEIGHT, MENU_FONT_WIDTH, 
		MENU_FONT_WEIGHT, false, std::wstring(L"Î¢ÈíÑÅºÚ"));

	return D3D_OK;
}

int	CGraphics::SpriteInit()
{
	//m_pSprite[SPRITE_BKGROUND] = LoadSprite(std::wstring(L"./Assets/BattleField.png"), /*WND_WIDTH, WND_HEIGHT*/10, 10);
	//m_pSprite[SPRITE_BONZEDOG] = LoadSprite(std::wstring(L"./Assets/Bonze Dog/BonzeDog00.png"), SPRITE_WIDTH, SPRITE_HEIGHT);
	return D3D_OK;
}
bool CGraphics::InitBackgroundSurface()
{
	D3DXIMAGE_INFO	imageInfo;
	D3DXGetImageInfoFromFile(L"./Assets/BattleField.jpg", &imageInfo);

	m_ipDevice->CreateOffscreenPlainSurface(imageInfo.Width, imageInfo.Height,
		imageInfo.Format, D3DPOOL_SYSTEMMEM, &m_pImageSurface, NULL);// create a image surface.
	//Attention: we can only alloctae this surface on system main memory not on the graphic vedio card memory
	
	
	D3DXLoadSurfaceFromFile(m_pImageSurface, NULL, NULL, L"./Assets/BattleField.jpg",
		NULL, D3DX_FILTER_NONE, D3DCOLOR_ARGB(255, 0, 0, 0), NULL);// load background information to surface

	m_ipDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_pBackBufferSurface);

	return true;
}

void CGraphics::UpdateBackground()
{
	// the update surface function only should copy surface located on main memory 
	// to surface on vedio card memory
	m_ipDevice->UpdateSurface(m_pImageSurface, NULL, m_pBackBufferSurface, NULL);// if rect==null, point must be 0,0 or null
}

bool CGraphics::InitCursorSurface()
{
	D3DXIMAGE_INFO	cursorInfo;
	D3DXGetImageInfoFromFile(L"./Assets/DemonCursor.png", &cursorInfo);

	m_ipDevice->CreateOffscreenPlainSurface(cursorInfo.Width, cursorInfo.Height,
		cursorInfo.Format, D3DPOOL_SYSTEMMEM, &m_pCursorSurface, NULL);// create a image surface.
	//Attention: we can only alloctae this surface on system main memory not on the graphic vedio card memory
	
	
	D3DXLoadSurfaceFromFile(m_pCursorSurface, NULL, NULL, L"./Assets/DemonCursor.png",
		NULL, D3DX_FILTER_NONE, D3DCOLOR_ARGB(255, 255, 255, 255), NULL);// load background information to surface

	m_ipDevice->SetCursorProperties(/*cursorInfo.Width / 2*/0, /*cursorInfo.Width / 2*/0, m_pCursorSurface);
	m_ipDevice->ShowCursor(TRUE);// show the cursor.
	return true;
}

void CGraphics::SetCursorPosition(int x, int y)
{
	m_ipDevice->ShowCursor(TRUE);
	//m_ipDevice->SetCursorPosition(x, y, D3DCURSOR_IMMEDIATE_UPDATE);
}