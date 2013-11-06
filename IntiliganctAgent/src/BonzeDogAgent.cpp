#include "BonzeDogAgent.h"

extern bool g_ctrlKeyPressed;

// initilize the sprites count in each agent state
const unsigned int CBonzeDogAgent::m_StateSpriteNumMap[m_StateCount] = {
		m_WalkSpritesCount, 
		m_HeatRushSpritesCount
};
const std::wstring	CBonzeDogAgent::m_StateName[m_StateCount] = {
		//Idle,
		L"Walk",
		//Attack,
		//Fire,
		//HeatRushPrep,
		L"HeatRush"
};
//Can not initilize array member one by one!!
//const int CBonzeDogAgent::m_StateSpriteMap[Walk] = m_WalkSpritesCount;
//const int CBonzeDogAgent::m_StateSpriteMap[HeatRush] = m_HeatRushSpritesCount;

CBonzeDogAgent::CBonzeDogAgent()
	:
	m_frameCount(0),
	m_eCurStateID(Walk),
	m_curSpriteIndex(0),
	m_curFrameIndex(0),
	m_curPos_x(300),		
	m_curPos_y(300),
	m_curVelocity(0),	
	m_fMoveFunctor(g_pAgentWalkState),
	m_pCurState(g_pAgentWalkState)// int init state of agent  is walk state
{
	// initilize the animation pointer array
	for(int index = 0; index < m_StateCount; ++index)
		m_pAnimation[index] = NULL;
}

CBonzeDogAgent::~CBonzeDogAgent()
{
	// delete the memory malloced by animatedsprite class
	// the array do not need to delete, cause it is auto varible
	for(int index = 0; index < m_StateCount; ++index)
		delete m_pAnimation[index];
}

// Run the sprite Animation
void CBonzeDogAgent::ShowAnimation(bool show)
{
	assert(m_pAnimation != NULL);// animation is not null

	m_pAnimation[m_eCurStateID]->RunSprite(show, m_curPos_x, m_curPos_y, m_curSpriteIndex);
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
		
		pGraphic->LoadAnimation(wstrsFileBaseName.str(), m_StateSpriteNumMap[index], &m_pAnimation[index]);
	}
	return true;
}

// Update the agent data every frame.
void CBonzeDogAgent::Run()
{
	this->UpdateData();
	this->ShowAnimation(true);
	this->UpdateState();
}
void CBonzeDogAgent::UpdateState()
{
	m_pCurState->ExecuteState(this);
}
// this is an control stratergy actually
void CBonzeDogAgent::UpdateData()
{
	this->SpriteFrameIndexManu();		// show which frame
	this->MovingStrategy();				// do some moving strategy
	this->PositionManupulate();			// show position
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
// update agent position information
void CBonzeDogAgent::PositionManupulate()
{
	// update agent position information
	if(m_curPos_x <= 0)								m_curPos_x = 0;
	if(m_curPos_x >= WND_WIDTH - SPRITE_WIDTH)		m_curPos_x = WND_WIDTH - SPRITE_WIDTH;
	if(m_curPos_y <= 0)								m_curPos_y = 0;
	if(m_curPos_y >= WND_HEIGHT - SPRITE_HEIGHT)	m_curPos_y = WND_HEIGHT - SPRITE_HEIGHT;
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
	//����������˶����߼��ĳɻص��������ߺ������󽫻���ӵ����
	//++m_curPos_x;
	//++m_curPos_y;
	m_fMoveFunctor(m_curPos_x, m_curPos_y);// this is a functor now.
}
// change the current state to a new state
void CBonzeDogAgent::ChangeState(CState<CAgent>* pNewState)
{
	assert(pNewState && m_pCurState);
	m_pCurState->ExitState(this);			// leave the current state
	m_pCurState = pNewState;				// change state to a new one
	m_pCurState->EnterState(this);			// enter into a new state
}
bool CBonzeDogAgent::IsCtrlKeyPressed()
{
	return g_ctrlKeyPressed;
}
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
//�ı���������˶�����
void CBonzeDogAgent::SetMoveStrategy(CState<CAgent>* pNewState)
{
	m_fMoveFunctor.SetState(pNewState);
}