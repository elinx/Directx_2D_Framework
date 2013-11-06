#pragma	once
#include "Agent.h"
#include "BonzeDogAgent.h"
#include "State.h"

#define	g_pAgentHeatRushState CAgentHeatRushState::GetInstance()

class CAgentHeatRushState : public CState<CAgent> {

public:

	CAgentHeatRushState();
	virtual ~CAgentHeatRushState();	// why?
	virtual	void EnterState(CAgent* agent);
	virtual void ExecuteState(CAgent* agent);
	virtual void ExitState(CAgent* agent);
	
	enum EStateID GetStateID(){
		return m_eStateID;
	}
public:
	static CAgentHeatRushState* GetInstance();
	void MovingStrategy(int& x, int& y);
private:
	enum EStateID	m_eStateID;
};