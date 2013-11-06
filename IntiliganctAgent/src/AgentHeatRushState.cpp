#include "AgentHeatRushState.h"

CAgentHeatRushState::CAgentHeatRushState()
{
	m_eStateID = HeatRush;
}

CAgentHeatRushState::~CAgentHeatRushState()
{
}

CAgentHeatRushState* CAgentHeatRushState::GetInstance()
{
	static CAgentHeatRushState agentHeatRushState;
	return &agentHeatRushState;
}

void CAgentHeatRushState::EnterState(CBonzeDogAgent* agent)
{
	agent->SetCurStateID(HeatRush);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentHeatRushState);
}

void CAgentHeatRushState::ExecuteState(CBonzeDogAgent* agent)
{
	if(!(agent->IsCtrlKeyPressed()))
		agent->ChangeState(g_pAgentWalkState);
}

void CAgentHeatRushState::ExitState(CBonzeDogAgent* agent)
{}

void CAgentHeatRushState::MovingStrategy(int& x, int& y)
{
	x += 5;// very basic operation
	++y;
}