#include "Camera.h"
#include <cstdlib>

CCamera::CCamera()
	:
	m_iPosX(0),
	m_iPosY(0),
	m_iLastX(0),
	m_iLastY(0)
{
	CoordModify(m_iLastX, m_iLastY);
	CoordModify(m_iPosX, m_iPosY);
}
CCamera::CCamera(int ax, int ay)
	:
	m_iPosX(ax - WND_WIDTH / 2),
	m_iPosY(ay - WND_HEIGHT / 2),
	m_iLastX(ax - WND_WIDTH / 2),
	m_iLastY(ay - WND_HEIGHT / 2)
{
	CoordModify(m_iLastX, m_iLastY);
	CoordModify(m_iPosX, m_iPosY);
}
CCamera::~CCamera()
{
}

int CCamera::GetPosX()
{
	return m_iLastX;// Note: here is the last position
}
int CCamera::GetPosY()
{
	return m_iLastY;
}
// update the camera every frame only when the camera pos 
// is laarge than the specific distance
void CCamera::Update(int agentRelativeX, int agentRelativeY)
{
	m_iPosX += agentRelativeX;
	m_iPosY += agentRelativeY;
	CoordModify(m_iPosX, m_iPosY);
	
	if(abs(m_iPosX - m_iLastX) > 0 || abs(m_iPosY - m_iLastY) > 0)
	{
		m_iLastX = m_iPosX;
		m_iLastY = m_iPosY;
	}
}
// the camera coordiate should not be beyond the map
void CCamera::CoordModify(int& x, int& y)
{
	//x -= WND_WIDTH / 2;//Every time try to put agent in the center of the camera/view
	//y -= WND_HEIGHT / 2;
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x >= MAP_WIDTH - WND_WIDTH) x = MAP_WIDTH - WND_WIDTH;
	if(y >= MAP_HEIGHT - WND_HEIGHT) y = MAP_HEIGHT - WND_HEIGHT;
}