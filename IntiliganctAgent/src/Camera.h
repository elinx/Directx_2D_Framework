#pragma once

class CCamera {
public:
	CCamera();
	~CCamera();

	int GetPosX();
	int GetPosY();
	void Update(int agentRelativeX, int agentRelativeY);			// To update the coordiante of the camera

private:
	void CoordModify(int& x, int& y);

private:
	int				m_iPosX;
	int				m_iPosY;	// The coordinate of the up left corner point
	int				m_iLastX;
	int				m_iLastY;	// Record the camera pos
};