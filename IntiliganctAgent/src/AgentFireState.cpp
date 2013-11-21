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
	fcout << "Enter into fire state." << std::endl;
	agent->SetCurStateID(Fire);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentFireState);
}

void CAgentFireState::ExecuteState(CBonzeDogAgent* agent)
{
	if(! g_pDirectInput->IsKeyPressed(DIK_SPACE))// if the space is not pressed, change state fo idle state
		agent->ChangeState(g_pAgentIdleState);
	else if(agent->HasFrameFinished())
	{
		//agent->ChangeState(g_pAgentWalkState);
		agent->Fire();
	}
}

void CAgentFireState::ExitState(CBonzeDogAgent* agent)
{
	fcout << "Exit from fire state." << std::endl;
}

void CAgentFireState::MovingStrategy(CBonzeDogAgent* agent)
{
	//keep steady!
}