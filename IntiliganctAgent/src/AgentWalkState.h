#pragma	once
//#include "Agent.h"
#include "BonzeDogAgent.h"
#include "State.h"
#include <cmath>

class CBonzeDogAgent;// If I do not add this line, the class below can't find this class, WHY?!

#define	g_pAgentWalkState CAgentWalkState::GetInstance()

class CAgentWalkState : public CState<CBonzeDogAgent> {
public:
	CAgentWalkState();
	virtual ~CAgentWalkState();	// why?
	virtual	void EnterState(CBonzeDogAgent* agent);
	virtual void ExecuteState(CBonzeDogAgent* agent);
	virtual void ExitState(CBonzeDogAgent* agent);

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