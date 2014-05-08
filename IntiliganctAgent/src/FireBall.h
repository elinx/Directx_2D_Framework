#pragma once

#include <iostream>
#include "Agent.h"
#include "BallStates.h"
#include "AnimatedSprite.h"
#include "Graphics.h"
#include <fstream>
extern std::ofstream fcout;

class CFireBall : public CAgent {
public:
	CFireBall();
	~CFireBall();
	
	// virtual functons inherrited from agent class
	virtual void Run(int cx, int cy);											// main run function, update starts from here.
	virtual void UpdateData();									// update agent data every frame
	virtual void UpdateState();									// update agent state every frame
	virtual	bool InitAgent(CGraphics* pGraphic);				// init agent called by upper(referenced) calss			

	void	ChangeState(CState<CFireBall>* pNewState);
	void	SetPosX(int x);
	void	SetPosY(int y);
	int		GetPosX(){
		return m_curPos_x;
	}
	int		GetPosY(){
		return m_curPos_y;
	}
	bool	HasFireEnd();
	void	FireEnd(bool yes);
	bool	CFireBall::HasFrameFinished();
	void	SetFireDirection(bool reverse);
	bool	GetFireDirection();
private:
	void ShowAnimation(bool show);								//show the sprite Animation
	bool LoadSprite(CGraphics* pGraphic);						// init the agent information needed
private:
	int							m_curPos_x;
	int							m_curPos_y;
	int							m_direction_x;					// the dog can only fire straightly
	int							m_direction_y;					// so only define this two direction

	EBallStateID				m_eCurBallStateID;				// to hold the state of ball

	static const int			m_StartSpritesCount = 2;		// the start state only has two sprites
	static const int			m_StopSpritesCount = 2;			// and the stop state has three sprites
	static const int			m_ballStateCount = 2;			// the ball only have to state
																// hold the sprites count of state for loading iamges
	static const unsigned int	m_StateSpriteNumMap[m_ballStateCount];
																// hold the state name for loading images
	static const std::wstring	m_StateNameMap[m_ballStateCount];
																// hold the animation of each state
	CAnimatedSprite*			m_pAnimation[m_ballStateCount];	
																// hold the sprites width/height of each state
	static const SPRITEWH		m_pStateSpriteWH[m_ballStateCount];

	CState<CFireBall>*			m_pCurState;					// current state pointer

	unsigned int				m_curSpriteIndex;				// hold the current index of the animation
	bool						m_FireFinished;
	bool						m_ReverseFlag;
};