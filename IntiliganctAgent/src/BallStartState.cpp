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

void CBallStartState::MovingStrategy(int& x, int& y)
{
	//x += 5;// very basic operation
	//++y;
	//y -= 100;
	//y += 1;
	x += 15;
}