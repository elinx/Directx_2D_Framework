#include "Camera.h"
#include <cstdlib>

CCamera::CCamera()
	:
	m_iPosX(0),
	m_iPosY(0),
	m_iLastX(0),
	m_iLastY(0)
{
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
	
	if(abs(m_iPosX - m_iLastX) > 10 || abs(m_iPosY - m_iLastY) > 10)
	{
		m_iLastX = m_iPosX;
		m_iLastY = m_iPosY;
	}
}
// the camera coordiate should not be beyond the map
void CCamera::CoordModify(int& x, int& y)
{
	if(x < 0) x = 0;
	if(y < 0) y = 0;
	if(x >= 2400) x = 2400;
	if(y >= 2600) y = 2600;
}