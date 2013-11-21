#pragma	once
//#include "Agent.h"
#include "BonzeDogAgent.h"
#include "State.h"
#include <cmath>

class CBonzeDogAgent;// If I do not add this line, the class below can't find this class, WHY?!

#define	g_pAgentIdleState CAgentIdleState::GetInstance()

class CAgentIdleState : public CState<CBonzeDogAgent> {
public:
	CAgentIdleState();
	virtual ~CAgentIdleState();	// why?
	virtual	void EnterState(CBonzeDogAgent* agent);
	virtual void ExecuteState(CBonzeDogAgent* agent);
	virtual void ExitState(CBonzeDogAgent* agent);

	enum EStateID GetStateID(){
		return m_eStateID;
	}
public:
	static CAgentIdleState* GetInstance();
	void MovingStrategy(CBonzeDogAgent* agent);
private:
	enum EStateID	m_eStateID;
	double			m_theta;// 沿着圆心旋转的theta角
};