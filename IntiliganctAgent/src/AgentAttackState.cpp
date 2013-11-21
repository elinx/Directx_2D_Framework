#include "AgentAttackState.h"

CAgentAttackState::CAgentAttackState()
{
	m_eStateID = Attack;
}

CAgentAttackState::~CAgentAttackState()
{
}

CAgentAttackState* CAgentAttackState::GetInstance()
{
	static CAgentAttackState agentAttackState;
	return &agentAttackState;
}

void CAgentAttackState::EnterState(CBonzeDogAgent* agent)
{
	fcout << "Enter into attack state." << std::endl;
	agent->SetCurStateID(Attack);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentAttackState);
}

void CAgentAttackState::ExecuteState(CBonzeDogAgent* agent)
{
	if((! g_pDirectInput->IsKeyPressed(DIK_LCONTROL))
		&& (agent->HasFrameFinished()))// if the left control key is not pressed, change state fo idle state
		agent->ChangeState(g_pAgentIdleState);
}

void CAgentAttackState::ExitState(CBonzeDogAgent* agent)
{
	fcout << "Exit from attack state." << std::endl;
}

void CAgentAttackState::MovingStrategy(CBonzeDogAgent* agent)
{
	//keep steady!
}