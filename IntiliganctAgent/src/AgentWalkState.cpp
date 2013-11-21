#include "AgentWalkState.h"

CAgentWalkState::CAgentWalkState()
	:
m_theta(0)
{
	m_eStateID = Walk;
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
	fcout << "Enter into walk state." << std::endl;
	agent->SetCurStateID(Walk);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentWalkState);
}

void CAgentWalkState::ExecuteState(CBonzeDogAgent* agent)
{
	//if(g_pDirectInput->IsKeyPressed(DIK_LCONTROL))
	//	agent->ChangeState(g_pAgentHeatRushState);
	//if(g_pDirectInput->IsKeyPressed(DIK_LALT))
	//	agent->ChangeState(g_pAgentAttackState);
	if(g_pDirectInput->IsKeyPressed(DIK_SPACE))// if the space key is pressed, change state fo fire state
		agent->ChangeState(g_pAgentFireState);
	else if(agent->HasFrameFinished())
		agent->ChangeState(g_pAgentIdleState);// else, change to idle state
}

void CAgentWalkState::ExitState(CBonzeDogAgent* agent)
{
	fcout << "Exit from walk state." << std::endl;
}

void CAgentWalkState::MovingStrategy(CBonzeDogAgent* agent)
{						
	int factor = 1;
	if(agent->MoveReverse())
		factor = -1;
	agent->SetAgentPosX(agent->GetAgentPosX() + 1 * factor);
}