#pragma	once
#include "Agent.h"
#include "BonzeDogAgent.h"
#include "State.h"
#include <cmath>

#define	g_pAgentWalkState CAgentWalkState::GetInstance()

class CAgentWalkState : public CState<CAgent> {
public:
	CAgentWalkState();
	virtual ~CAgentWalkState();	// why?
	virtual	void EnterState(CAgent* agent);
	virtual void ExecuteState(CAgent* agent);
	virtual void ExitState(CAgent* agent);

	enum EStateID GetStateID(){
		return m_eStateID;
	}
public:
	static CAgentWalkState* GetInstance();
	void MovingStrategy(int& x, int& y);
private:
	enum EStateID	m_eStateID;
	double			m_theta;// 沿着圆心旋转的theta角
};