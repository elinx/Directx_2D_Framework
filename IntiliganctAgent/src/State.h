#pragma	once

/* this is a base state class template, 
 * all state in this project should 
 * inherited from this class.
 */
template<typename Entity>
class	CState {
public:
	virtual ~CState() {};	// why?, and this should implement EXACTLLY!!
	virtual	void EnterState(Entity* entity) = 0;
	virtual void ExecuteState(Entity* entity) = 0;
	virtual void ExitState(Entity* entity) = 0;
	virtual void MovingStrategy(int& x, int& y) = 0;
};