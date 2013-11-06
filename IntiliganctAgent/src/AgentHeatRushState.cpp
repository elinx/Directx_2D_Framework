#include "AgentHeatRushState.h"

CAgentHeatRushState::CAgentHeatRushState()
{
	//m_eStateID = HeatRush;
}

CAgentHeatRushState::~CAgentHeatRushState()
{
}

CAgentHeatRushState* CAgentHeatRushState::GetInstance()
{
	static CAgentHeatRushState agentHeatRushState;
	return &agentHeatRushState;
}

void CAgentHeatRushState::EnterState(CAgent* agent)
{
	((CBonzeDogAgent*)agent)->SetCurStateID(HeatRush);
	((CBonzeDogAgent*)agent)->ClearSpriteIndex();
	((CBonzeDogAgent*)agent)->SetMoveStrategy(g_pAgentHeatRushState);
}

void CAgentHeatRushState::ExecuteState(CAgent* agent)
{
	if(!((CBonzeDogAgent*)agent)->IsCtrlKeyPressed())
		((CBonzeDogAgent*)agent)->ChangeState(g_pAgentWalkState);
}

void CAgentHeatRushState::ExitState(CAgent* agent)
{}

void CAgentHeatRushState::MovingStrategy(int& x, int& y)
{
	x += 5;// very basic operation
	++y;
}