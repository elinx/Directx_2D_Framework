#include "AgentFireState.h"

CAgentFireState::CAgentFireState()
{
	m_eStateID = Fire;
}

CAgentFireState::~CAgentFireState()
{
}

CAgentFireState* CAgentFireState::GetInstance()
{
	static CAgentFireState agentFireState;
	return &agentFireState;
}

void CAgentFireState::EnterState(CBonzeDogAgent* agent)
{
	agent->SetCurStateID(Fire);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentFireState);
}

void CAgentFireState::ExecuteState(CBonzeDogAgent* agent)
{
	//if(!(agent->IsLALTKeyPressed()))
	if(agent->HasFrameFinished())
		agent->ChangeState(g_pAgentWalkState);
}

void CAgentFireState::ExitState(CBonzeDogAgent* agent)
{}

void CAgentFireState::MovingStrategy(int& x, int& y)
{
	//x += 5;// very basic operation
	//++y;
	//y -= 100;
	y += 1;
}