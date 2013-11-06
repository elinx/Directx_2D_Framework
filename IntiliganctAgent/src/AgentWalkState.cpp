#include "AgentWalkState.h"

CAgentWalkState::CAgentWalkState()
	:
m_theta(0)
{
	//m_eStateID = Walk;
}

CAgentWalkState::~CAgentWalkState()
{
}

CAgentWalkState* CAgentWalkState::GetInstance()
{
	static CAgentWalkState agentWalkState;
	return &agentWalkState;
}

void CAgentWalkState::EnterState(CAgent* agent)
{
	((CBonzeDogAgent*)agent)->SetCurStateID(Walk);
	((CBonzeDogAgent*)agent)->ClearSpriteIndex();
	((CBonzeDogAgent*)agent)->SetMoveStrategy(g_pAgentWalkState);
}

void CAgentWalkState::ExecuteState(CAgent* agent)
{
	if(((CBonzeDogAgent*)agent)->IsCtrlKeyPressed())
		((CBonzeDogAgent*)agent)->ChangeState(g_pAgentHeatRushState);
}

void CAgentWalkState::ExitState(CAgent* agent)
{
}

void CAgentWalkState::MovingStrategy(int& x, int& y)
{						
	// most straight forward moving method
	// ++x;
	// ++y;

	// ÑØ×ÅÔ²È¦×ß,°ë¾¶Îª50p
	x = 300 + 200 * std::cos(m_theta);
	y = 300 + 200 * std::sin(m_theta);
	m_theta += 2 * PI / 360;
}