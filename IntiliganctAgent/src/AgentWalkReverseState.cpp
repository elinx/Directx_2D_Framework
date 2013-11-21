//#include "AgentWalkReverseState.h"
//
//CAgentWalkReverseState::CAgentWalkReverseState()
//	:
//m_theta(0)
//{
//	//m_eStateID = WalkReverse;
//}
//
//CAgentWalkReverseState::~CAgentWalkReverseState()
//{
//}
//
//CAgentWalkReverseState* CAgentWalkReverseState::GetInstance()
//{
//	static CAgentWalkReverseState agentWalkReverseState;
//	return &agentWalkReverseState;
//}
//
//void CAgentWalkReverseState::EnterState(CBonzeDogAgent* agent)
//{
//	fcout << "Enter into walk reverse state." << std::endl;
//	//agent->SetCurStateID(WalkReverse);
//	agent->ClearSpriteIndex();
//	agent->SetMoveStrategy(g_pAgentWalkReverseState);
//}
//
//void CAgentWalkReverseState::ExecuteState(CBonzeDogAgent* agent)
//{
//	if(g_pDirectInput->IsKeyPressed(DIK_SPACE))// if the space key is pressed, change state fo fire state
//		agent->ChangeState(g_pAgentFireState);
//	else if(agent->HasFrameFinished())
//		agent->ChangeState(g_pAgentIdleState);// else, change to idle state
//}
//
//void CAgentWalkReverseState::ExitState(CBonzeDogAgent* agent)
//{
//	fcout << "Exit from walk reverse state." << std::endl;
//}
//
//void CAgentWalkReverseState::MovingStrategy(CBonzeDogAgent* agent)
//{						
//	// Walk reverse to the normal direction.
//	//x -= 1;
//}