#include "AgentIdleState.h"

CAgentIdleState::CAgentIdleState()
	:
m_theta(0)
{
	m_eStateID = Idle;
}

CAgentIdleState::~CAgentIdleState()
{
}

CAgentIdleState* CAgentIdleState::GetInstance()
{
	static CAgentIdleState agentIdleState;
	return &agentIdleState;
}

void CAgentIdleState::EnterState(CBonzeDogAgent* agent)
{
	fcout << "Enter into idle state." << std::endl;
	agent->SetCurStateID(Idle);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentIdleState);
}

void CAgentIdleState::ExecuteState(CBonzeDogAgent* agent)
{
	if(g_pDirectInput->IsKeyPressed(DIK_LCONTROL))			// left ctrl key pressed, change to Attack state
		agent->ChangeState(g_pAgentAttackState);
	if(g_pDirectInput->IsKeyPressed(DIK_LALT))				// left alt key pressed, change to HeatRush state
		agent->ChangeState(g_pAgentHeatRushState);
	if(g_pDirectInput->IsKeyPressed(DIK_LEFTARROW))			// left arrow key pressed, change to walk-reverse state
	{
		agent->ChangeState(g_pAgentWalkState);
		agent->MoveDirection(true);							// the agent is waling in the reversed direction
	}
	if(g_pDirectInput->IsKeyPressed(DIK_RIGHTARROW))		// right arrow key pressed, change to walk state
	{
		agent->ChangeState(g_pAgentWalkState);
		agent->MoveDirection(false);							// the agent is waling in the reversed direction
	}
	if(g_pDirectInput->IsKeyPressed(DIK_SPACE))				// space key pressed, change to space state
		agent->ChangeState(g_pAgentFireState);
}

void CAgentIdleState::ExitState(CBonzeDogAgent* agent)
{
	fcout << "Exit from idle state." << std::endl;
}

void CAgentIdleState::MovingStrategy(CBonzeDogAgent* agent)
{						
	//keep steady
}