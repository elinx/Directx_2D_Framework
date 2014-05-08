#include "BonzeDogAgent.h"

//extern bool g_ctrlKeyPressed;
//extern bool g_laltKeyPressed;

// initilize the sprites count in each agent state
const unsigned int CBonzeDogAgent::m_StateSpriteNumMap[m_StateCount] = {
		m_IdleSpritesCount,
		m_WalkSpritesCount, 
		//m_WalkReverseSpritesCount,
		m_AttackSpritesCount,
		m_FireSpritesCount,
		m_HeatRushSpritesCount
};
const std::wstring	CBonzeDogAgent::m_StateName[m_StateCount] = {
		L"Idle",
		L"Walk",
		//L"WalkReverse",
		L"Attack",
		L"Fire",
		L"HeatRush"
};
const SPRITEWH	CBonzeDogAgent::m_pStateSpriteWH[m_StateCount] = {
	{95, 60},
	{90, 60},
	//{90, 60},
	{105, 75},
	{119, 80},
	{110, 70}
};
//Can not initilize array member one by one!!
//const int CBonzeDogAgent::m_StateSpriteMap[Walk] = m_WalkSpritesCount;
//const int CBonzeDogAgent::m_StateSpriteMap[HeatRush] = m_HeatRushSpritesCount;

CBonzeDogAgent::CBonzeDogAgent()
	:
	m_frameCount(0),
	m_curSpriteIndex(0),
	m_curFrameIndex(0),
	m_curPos_x(300),		
	m_curPos_y(300),
	m_lastPos_x(300),
	m_lastPos_y(300),
	m_relativePos_x(0),
	m_relativePos_y(0),
	m_curVelocity(0),	
	m_direction_x(PDIRECTION),
	m_direction_y(PDIRECTION),
	m_eCurStateID(Idle),
	m_pReverseFlag(false),
	m_fMoveFunctor(g_pAgentIdleState),
	m_pCurState(g_pAgentIdleState)// int init state of agent  is walk state
{
	fcout << "CBonzeDogAgent::ctor" << std::endl;
	// initilize the animation pointer array
	for(int index = 0; index < m_StateCount; ++index)
		m_pAnimation[index] = NULL;
	m_pFireBall = new CFireBall();
}

CBonzeDogAgent::~CBonzeDogAgent()
{
	fcout << "CBonzeDogAgent::detor" << std::endl;
	// delete the memory malloced by animatedsprite class
	// the array do not need to delete, cause it is auto varible
	for(int index = 0; index < m_StateCount; ++index)
		delete m_pAnimation[index];
	delete m_pFireBall;
	//MessageBox(NULL, L"FireBall Be Deleted", L"Error", 0);
}

// Run the sprite Animation
void CBonzeDogAgent::ShowAnimation(bool reverse, int cx, int cy)
{
	assert(m_pAnimation != NULL);// animation is not null
	//fcout << "CBonzeDogAgent::ShowAnimation()" << std::endl;
	m_pAnimation[m_eCurStateID]->RunSprite(reverse, m_curPos_x - cx, m_curPos_y - cy, m_curSpriteIndex);
}

//init the agent information needed
bool CBonzeDogAgent::LoadSprite(CGraphics* pGraphic)
{
	assert(pGraphic != NULL);// pGraphic not null

	// load the sprite in the spefic directory into animation pointer
	// remember to free the memory malloced by this function
	for(int index = 0; index < m_StateCount; ++index)
	{
		std::wstringstream wstrsFileBaseName;
		wstrsFileBaseName << L"./Assets/Bronze Dog/" << m_StateName[index] << L"/" << m_StateName[index];
		
		pGraphic->LoadAnimation(wstrsFileBaseName.str(), m_StateSpriteNumMap[index], &m_pAnimation[index],
			m_pStateSpriteWH[index].width, m_pStateSpriteWH[index].height);
	}
	m_pFireBall->InitAgent(pGraphic);
	return true;
}

// Update the agent data every frame.
void CBonzeDogAgent::Run(int cx, int cy)
{
	//fcout << "CBonzeDogAgent::Run" << std::endl;
	this->UpdateData();
	this->UpdateState();
	this->ShowAnimation(m_pReverseFlag, cx, cy);// Change the order of updatestate and show animation.
	if(!m_pFireBall->HasFireEnd())
		m_pFireBall->Run(0, 0);
}
void CBonzeDogAgent::UpdateState()
{
	//fcout << "CBonzeDogAgent::UpdateState" << std::endl;
	m_pCurState->ExecuteState(this);
}
// this is an control stratergy actually
void CBonzeDogAgent::UpdateData()
{
	//fcout << "CBonzeDogAgent::UpdateData" << std::endl;
	this->SpriteFrameIndexManu();		// show which frame
	this->MovingStrategy();				// do some moving strategy
	this->PositionManupulate();			// show position
	this->UpdateRelativeCoord();
}
void CBonzeDogAgent::UpdateRelativeCoord()
{
	m_relativePos_x = m_curPos_x - m_lastPos_x;
	m_relativePos_y = m_curPos_y - m_lastPos_y;

	m_lastPos_x = m_curPos_x;
	m_lastPos_y = m_curPos_y;
}
//update sprite index to show
void CBonzeDogAgent::SpriteFrameIndexManu()
{
	++m_frameCount;
	if(m_frameCount > SPRITE_FRAMESPEED)
	{
		++m_curSpriteIndex;
		if(m_curSpriteIndex > m_StateSpriteNumMap[m_eCurStateID] - 1) // index num is 0..N-1
			m_curSpriteIndex = 0;
		
		m_frameCount = 0;
	}
}
// update agent position information, befor show the animation
void CBonzeDogAgent::PositionManupulate()
{
	// update agent position information
	if(m_curPos_x <= 0)								m_curPos_x = 0;
	if(m_curPos_x >= MAP_WIDTH - SPRITE_WIDTH)		m_curPos_x = MAP_WIDTH - SPRITE_WIDTH;//TODO:lsjfsl
	if(m_curPos_y <= 0)								m_curPos_y = 0;
	if(m_curPos_y >= MAP_HEIGHT - SPRITE_HEIGHT)	m_curPos_y = MAP_HEIGHT - SPRITE_HEIGHT;
}
// load sprite image into this object
bool CBonzeDogAgent::InitAgent(CGraphics* pGraphic)
{
	assert(pGraphic != NULL);

	return LoadSprite(pGraphic);
}
// some ai moving strategy
void CBonzeDogAgent::MovingStrategy()
{
	//这里如果把运动的逻辑改成回调函数或者函数对象将会更加的灵活
	m_fMoveFunctor(this);// this is a functor now.
}
// change the current state to a new state
void CBonzeDogAgent::ChangeState(CState<CBonzeDogAgent>* pNewState)
{
	assert(pNewState && m_pCurState);
	m_pCurState->ExitState(this);			// leave the current state
	m_pCurState = pNewState;				// change state to a new one
	m_pCurState->EnterState(this);			// enter into a new state
}
//bool CBonzeDogAgent::IsCtrlKeyPressed()
//{
//	//return g_ctrlKeyPressed;
//	return g_pDirectInput->IsKeyPressed(DIK_LCONTROL);
//}
//bool CBonzeDogAgent::IsLALTKeyPressed()
//{
//	//return g_laltKeyPressed;
//	return g_pDirectInput->IsKeyPressed(DIK_LALT);
//}
// change the current id
void CBonzeDogAgent::SetCurStateID(EStateID stateID)
{
	m_eCurStateID = stateID;
}
// clear the current sprite index, cos diffent frame has 
// different sprites number.
void CBonzeDogAgent::ClearSpriteIndex()
{
	m_curSpriteIndex = 0;
}
// change the moving strategy of agent
void CBonzeDogAgent::SetMoveStrategy(CState<CBonzeDogAgent>* pNewState)
{
	m_fMoveFunctor.SetState(pNewState);
}

// to check whether this frame has finished
bool CBonzeDogAgent::HasFrameFinished()
{
	return ((m_curSpriteIndex + 1) == m_StateSpriteNumMap[m_eCurStateID]);
}
// get the current x position
int	CBonzeDogAgent::GetAgentPosX(){
	return m_curPos_x;
}
// get the current y position
int	CBonzeDogAgent::GetAgentPosY(){
	return m_curPos_y;
}
void CBonzeDogAgent::SetAgentPosX(int x)
{
	m_curPos_x = x;
}
void CBonzeDogAgent::SetAgentPosY(int y)
{
	m_curPos_y = y;
}
// get the current x direction
int	CBonzeDogAgent::GetAgentDirectionX()
{
	return m_direction_x;
}
// get the current y direction
int	CBonzeDogAgent::GetAgentDirectionY()
{
	return m_direction_y;
}
// set the current x direction
void CBonzeDogAgent::ChangeAgentDirectionX(int direction)
{
	m_direction_x = direction;
}
// set the current y direction
void CBonzeDogAgent::ChangeAgentDirectionY(int direction)
{
	m_direction_y;
}

void CBonzeDogAgent::Fire()
{	
	fcout << "Start CBonzeDogAgent::Fire()" << std::endl;
    m_pFireBall->SetPosX(m_curPos_x + 90 );
	m_pFireBall->SetPosY(m_curPos_y + 40 );
	m_pFireBall->SetFireDirection(m_pReverseFlag);
	// Do not use a thread to show graphic stuffs!!!!
	// Just execute the run method of cfireball class in a seperate thread.
	//boost::thread fireThread(&CFireBall::Run, m_pFireBall);
	//m_fireThread.join();

	m_pFireBall->FireEnd(false);	// Start Fire
	fcout << "Exit CBonzeDogAgent::Fire()" << std::endl;
}
// get the x distance of agent moved relative to the last frame
int	CBonzeDogAgent::GetRelativeX()
{
	return m_relativePos_x;
}
// get the y distance of agent moved relative to the last frame
int	CBonzeDogAgent::GetRelativeY()
{
	return m_relativePos_y;
}
// To dedicate whether the agent is in the reverse direction
bool CBonzeDogAgent::MoveReverse()
{
	return m_pReverseFlag;
}
// Set the direction of the agent move, forward or reverse?
void CBonzeDogAgent::MoveDirection(bool reverse)
{
	m_pReverseFlag = reverse;
}