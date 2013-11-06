#pragma	once

#include "Agent.h"
#include "State.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "WinConfigure.h"
#include "Graphics.h"
#include "AgentWalkState.h"
#include "AgentHeatRushState.h"
#include <assert.h>

//ö��������������ܴ��ڵ�״̬
enum EStateID {
	//Idle = 0,
	Walk = 0,
	//Attack,
	//Fire,
	//HeatRushPrep,
	HeatRush
};
//����һ�����������������ò�ͬ�Ŀ��Ʋ���
class FMoveStrategy {
public:
	FMoveStrategy(CState<CAgent>* state) { m_pState = state; };
	void SetState(CState<CAgent>* newState) { m_pState = newState; }

	void operator()(int& x, int& y) {
		m_pState->MovingStrategy(x, y);
	}
private:
	CState<CAgent>* m_pState;
};

class CBonzeDogAgent : public CAgent {
public:
	CBonzeDogAgent();							//contor
	~CBonzeDogAgent();							//detor

	virtual void Run();							//main run function, update starts from here.
	virtual void UpdateData();					//update agent data every frame
	virtual void UpdateState();					//update agent state every frame
	virtual	bool InitAgent(CGraphics* pGraphic);

	void	ChangeState(CState<CAgent>* pNewState);
	bool	IsCtrlKeyPressed();
	void	SetCurStateID(EStateID stateID);
	void	ClearSpriteIndex();
	void	SetMoveStrategy(CState<CAgent>* pNewState);
private:
	void ShowAnimation(bool show);				//show the sprite Animation
	bool LoadSprite(CGraphics* pGraphic);		//init the agent information needed
	void PositionManupulate();					//Position Manupulate
	void SpriteFrameIndexManu();				//manupulate the frame index to show
	void MovingStrategy();						//how to move

private:										// There are 6 sprites in this animation
	static const int			m_WalkSpritesCount = 6;//record the frame count, to update the speed of the agent
	static const int			m_HeatRushSpritesCount = 4;
	static const int			m_StateCount = 2;

												// To hold how many sprites in each state
	static const unsigned int	m_StateSpriteNumMap[m_StateCount];
												// to enum the id name
	static const std::wstring	m_StateName[m_StateCount];			
												//animation data stored, two state pointer array, NOT OBJECT
	CAnimatedSprite*			m_pAnimation[m_StateCount];	
	CState<CAgent>*				m_pCurState;	//current state pointer

	EStateID					m_eCurStateID;	//hold the current state id
	unsigned int				m_frameCount;
	unsigned int				m_curSpriteIndex;// which frame is randered now	
	unsigned int				m_curFrameIndex;
	int							m_curPos_x;		//may be negative
	int							m_curPos_y;
	unsigned int				m_curVelocity;	//the current speed of the agent

	FMoveStrategy				m_fMoveFunctor;
};