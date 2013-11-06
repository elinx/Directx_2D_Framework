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

void CAgentWalkState::EnterState(CBonzeDogAgent* agent)
{
	agent->SetCurStateID(Walk);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentWalkState);
}

void CAgentWalkState::ExecuteState(CBonzeDogAgent* agent)
{
	if(agent->IsCtrlKeyPressed())
		agent->ChangeState(g_pAgentHeatRushState);
}

void CAgentWalkState::ExitState(CBonzeDogAgent* agent)
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