#pragma	once

#include "Agent.h"
#include "State.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "WinConfigure.h"
#include "Graphics.h"
#include "AgentWalkState.h"
#include "AgentHeatRushState.h"
#include "AgentAttackState.h"
#include "AgentFireState.h"
#include <assert.h>

//枚举所有智能体可能处于的状态
enum EStateID {
	//Idle = 0,
	Walk = 0,
	Attack,
	Fire,
	//HeatRushPrep,
	HeatRush
};

typedef	struct _SpriteWH {
	int width, height;
} SPRITEWH;

//声明一个函数对象，用于作用不同的控制策略
class FMoveStrategy {
public:
	FMoveStrategy(CState<CBonzeDogAgent>* state) { m_pState = state; };
	void SetState(CState<CBonzeDogAgent>* newState) { m_pState = newState; }

	void operator()(int& x, int& y) {
		m_pState->MovingStrategy(x, y);
	}
private:
	CState<CBonzeDogAgent>* m_pState;
};

class CBonzeDogAgent : public CAgent {
public:
	CBonzeDogAgent();							//ctor
	~CBonzeDogAgent();							//detor

	virtual void Run();							//main run function, update starts from here.
	virtual void UpdateData();					//update agent data every frame
	virtual void UpdateState();					//update agent state every frame
	virtual	bool InitAgent(CGraphics* pGraphic);

	void	ChangeState(CState<CBonzeDogAgent>* pNewState);
	bool	IsCtrlKeyPressed();
	bool	IsLALTKeyPressed();
	void	SetCurStateID(EStateID stateID);
	void	ClearSpriteIndex();
	void	SetMoveStrategy(CState<CBonzeDogAgent>* pNewState);
	bool	HasFrameFinished();

	int		GetAgentPosX(){
		return m_curPos_x;
	}
	int		GetAgentPosY(){
		return m_curPos_y;
	}
private:
	void ShowAnimation(bool show);				//show the sprite Animation
	bool LoadSprite(CGraphics* pGraphic);		//init the agent information needed
	void PositionManupulate();					//Position Manupulate
	void SpriteFrameIndexManu();				//manupulate the frame index to show
	void MovingStrategy();						//how to move

private:										// There are 6 sprites in this animation
	static const int			m_WalkSpritesCount = 6;//record the frame count, to update the speed of the agent
	static const int			m_HeatRushSpritesCount = 4;
	static const int			m_AttackSpritesCount = 11;
	static const int			m_FireSpritesCount = 13;
	static const int			m_StateCount = 4;

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
	unsigned int				m_curVelocity;	//the current speed of the agent

	FMoveStrategy				m_fMoveFunctor;
};