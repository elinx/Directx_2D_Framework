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
	agent->SetCurStateID(Attack);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentAttackState);
}

void CAgentAttackState::ExecuteState(CBonzeDogAgent* agent)
{
	if(!(agent->IsLALTKeyPressed()))
		agent->ChangeState(g_pAgentWalkState);
}

void CAgentAttackState::ExitState(CBonzeDogAgent* agent)
{}

void CAgentAttackState::MovingStrategy(int& x, int& y)
{
	//x += 5;// very basic operation
	//++y;
}