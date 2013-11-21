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
	fcout << "Enter into heat rush state." << std::endl;
	agent->SetCurStateID(HeatRush);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentHeatRushState);
}

void CAgentHeatRushState::ExecuteState(CBonzeDogAgent* agent)
{
	if((! g_pDirectInput->IsKeyPressed(DIK_LALT))
		&& (agent->HasFrameFinished()) )// if the left alt key is not pressed, change state fo idle state
		agent->ChangeState(g_pAgentIdleState);
}

void CAgentHeatRushState::ExitState(CBonzeDogAgent* agent)
{
	fcout << "Exit from heat rush state." << std::endl;
}

void CAgentHeatRushState::MovingStrategy(CBonzeDogAgent* agent)
{
	//x += 5;		// Run fast forward
	int factor = 1;
	if(agent->MoveReverse())
		factor = -1;
	agent->SetAgentPosX(agent->GetAgentPosX() + 5 * factor);
}