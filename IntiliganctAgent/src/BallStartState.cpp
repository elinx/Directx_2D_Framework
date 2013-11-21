#include "BallStates.h"

CBallStartState::CBallStartState()
{
	m_eStateID = EFireBallStartState;
}

CBallStartState::~CBallStartState()
{
}

CBallStartState* CBallStartState::GetInstance()
{
	static CBallStartState BallStartState;
	return &BallStartState;
}

void CBallStartState::EnterState(CFireBall* agent)
{
	//agent->SetCurStateID(Fire);
	//agent->ClearSpriteIndex();
	//agent->SetMoveStrategy(g_pBallStartState);
}

void CBallStartState::ExecuteState(CFireBall* agent)
{
	//if(!(agent->IsLALTKeyPressed()))
	//if(agent->HasFrameFinished())
    if( agent->GetPosX() > 750)
		agent->FireEnd(true);	// End fire
		//agent->ChangeState(g_pAgentWalkState);
}

void CBallStartState::ExitState(CFireBall* agent)
{}

void CBallStartState::MovingStrategy(CFireBall* agent)
{
	int factor = 1;
	if(agent->GetFireDirection())
		factor = -1;
	agent->SetPosX(agent->GetPosX() + 15 * factor);
}