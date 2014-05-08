#pragma	once

#include "Agent.h"
#include "State.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "WinConfigure.h"
#include "Graphics.h"
#include "AgentIdleState.h"
#include "AgentWalkState.h"
//#include "AgentWalkReverseState.h"
#include "AgentHeatRushState.h"
#include "AgentAttackState.h"
#include "AgentFireState.h"
#include "FireBall.h"
#include "DirectInput.h"
#include <assert.h>
#include <boost/thread.hpp>

extern CInput* g_pDirectInput;
extern std::ofstream fcout;

static const int			PDIRECTION = 1;		// positive direction
static const int			NDIRECTION = -1;	// negative direction

//enum all states of agent
enum EStateID {
	Idle = 0,
	Walk,
	//WalkReverse,
	Attack,
	Fire,
	HeatRush
};

//a functor for controling of agent.
class FMoveStrategy {
public:
	FMoveStrategy(CState<CBonzeDogAgent>* state) { m_pState = state; };
	void SetState(CState<CBonzeDogAgent>* newState) { m_pState = newState; }

	void operator()(CBonzeDogAgent* agent) {
		m_pState->MovingStrategy(agent);
	}
private:
	CState<CBonzeDogAgent>* m_pState;
};

class CBonzeDogAgent : public CAgent {
public:
	CBonzeDogAgent();							//ctor
	~CBonzeDogAgent();							//detor

	virtual void Run(int cx, int cy);							//main run function, update starts from here.
	virtual void UpdateData();					//update agent data every frame
	virtual void UpdateState();					//update agent state every frame
	virtual	bool InitAgent(CGraphics* pGraphic);

	void	ChangeState(CState<CBonzeDogAgent>* pNewState);
	//bool	IsCtrlKeyPressed();
	//bool	IsLALTKeyPressed();
	void	SetCurStateID(EStateID stateID);
	void	ClearSpriteIndex();
	void	SetMoveStrategy(CState<CBonzeDogAgent>* pNewState);
	bool	HasFrameFinished();

	int		GetAgentPosX();
	int		GetAgentPosY();
	void	SetAgentPosX(int x);
	void	SetAgentPosY(int y);

	int		GetAgentDirectionX();
	int		GetAgentDirectionY();
	void	ChangeAgentDirectionX(int direction);
	void	ChangeAgentDirectionY(int direction);

	void	Fire();

	int		GetRelativeX();
	int		GetRelativeY();
	bool	MoveReverse();
	void	MoveDirection(bool reverse);
private:
	void ShowAnimation(bool reverse, int cx, int cy);//show the sprite Animation
	bool LoadSprite(CGraphics* pGraphic);		//init the agent information needed
	void PositionManupulate();					//Position Manupulate
	void SpriteFrameIndexManu();				//manupulate the frame index to show
	void MovingStrategy();						//how to move
	void UpdateRelativeCoord();
private:										// There are 6 sprites in this animation
	static const int			m_IdleSpritesCount = 6;
	static const int			m_WalkSpritesCount = 6;//record the frame count, to update the speed of the agent
	//static const int			m_WalkReverseSpritesCount = 6;
	static const int			m_HeatRushSpritesCount = 4;
	static const int			m_AttackSpritesCount = 11;
	static const int			m_FireSpritesCount = 13;
	static const int			m_StateCount = 5;

												// To hold how many sprites in each state
	static const unsigned int	m_StateSpriteNumMap[m_StateCount];
												// to enum the id name
	static const std::wstring	m_StateName[m_StateCount];			
												//animation data stored, two state pointer array, NOT OBJECT
	CAnimatedSprite*			m_pAnimation[m_StateCount];	
	static const SPRITEWH		m_pStateSpriteWH[m_StateCount];

	CState<CBonzeDogAgent>*		m_pCurState;	//current state pointer

	EStateID					m_eCurStateID;	//hold the current state id
	unsigned int				m_frameCount;
	unsigned int				m_curSpriteIndex;// which frame is randered now	
	unsigned int				m_curFrameIndex;
	int							m_curPos_x;		//may be negative
	int							m_curPos_y;
	int							m_lastPos_x;
	int							m_lastPos_y;
	int							m_relativePos_x;
	int							m_relativePos_y;
	unsigned int				m_curVelocity;	//the current speed of the agent

	FMoveStrategy				m_fMoveFunctor;

	int							m_direction_x;	// x direction of agent
	int							m_direction_y;	// y direction of agent

	CFireBall*					m_pFireBall;
	bool						m_pReverseFlag;
};