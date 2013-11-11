#pragma once

// enum all states of ball can stay
typedef enum _ballstate {
	EFireBallStartState = 0,
	EFireBallStopState
}EBallStateID;

#include "State.h"
#include "FireBall.h"

class CFireBall;// If I do not add this line, the class below can't find this class, WHY?!

#define	g_pBallStartState CBallStartState::GetInstance()

class CBallStartState : public CState<CFireBall> {
public:

	CBallStartState();
	virtual ~CBallStartState();	// why?
	virtual	void EnterState(CFireBall* agent);
	virtual void ExecuteState(CFireBall* agent);
	virtual void ExitState(CFireBall* agent);
	
	EBallStateID GetStateID(){
		return m_eStateID;
	}
public:
	static CBallStartState* GetInstance();
	void MovingStrategy(int& x, int& y);

private:
	EBallStateID	m_eStateID;
};