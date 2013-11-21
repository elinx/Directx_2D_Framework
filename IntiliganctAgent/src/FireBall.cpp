#include "FireBall.h"

const unsigned int	CFireBall::m_StateSpriteNumMap[m_ballStateCount] = {
	m_StartSpritesCount,
	m_StopSpritesCount
};
													
const std::wstring	CFireBall::m_StateNameMap[m_ballStateCount] = {
	L"BallStart",
	L"BallStop"
};															

const SPRITEWH	CFireBall::m_pStateSpriteWH[m_ballStateCount] = {
	{16, 16},	//invalid number
	{56, 28}
};
// ctor
CFireBall::CFireBall()
	:
m_FireFinished(true),	// Not fire yet
m_curPos_x(0),
m_curPos_y(0),
m_ReverseFlag(false),
m_eCurBallStateID(EFireBallStartState),
m_pCurState(g_pBallStartState)	// init to start state
{
	fcout << "CFireBall::ctor" << std::endl;
	// initilize the animation pointer array
	for(int index = 0; index < m_ballStateCount; ++index)
		m_pAnimation[index] = NULL;
}
// detor
CFireBall::~CFireBall()
{
	fcout << "CFireBall::detor" << std::endl;
	// delete the memory malloced by animatedsprite class
	// the array do not need to delete, cause it is auto varible
	for(int index = 0; index < m_ballStateCount; ++index)
		delete m_pAnimation[index];
}

//init the agent information needed
bool CFireBall::LoadSprite(CGraphics* pGraphic)
{
	assert(pGraphic != NULL);// pGraphic not null

	// load the sprite in the spefic directory into animation pointer
	// remember to free the memory malloced by this function
	for(int index = 0; index < m_ballStateCount; ++index)
	{
		std::wstringstream wstrsFileBaseName;
		wstrsFileBaseName << L"./Assets/Bronze Dog/" << m_StateNameMap[index] << L"/" << m_StateNameMap[index];
		
		pGraphic->LoadAnimation(wstrsFileBaseName.str(), m_StateSpriteNumMap[index], &m_pAnimation[index],
			m_pStateSpriteWH[index].width, m_pStateSpriteWH[index].height);
	}
	return true;
}
// Run the sprite Animation
void CFireBall::ShowAnimation(bool show)
{
	assert(m_pAnimation != NULL);// animation is not null
	fcout << "CFireBall::ShowAnimation()" << std::endl;
	m_pAnimation[m_eCurBallStateID]->RunSprite(show, m_curPos_x, m_curPos_y, m_curSpriteIndex);
}
// main run function, update starts from here.
void CFireBall::Run()
{
	fcout << "CFireBall::Run()" << std::endl;
	m_FireFinished = false;
	//while(!HasFireEnd())
	{
		this->UpdateData();
		this->UpdateState();
		this->ShowAnimation(true);// Change the order of updatestate and show animation.
	}
}
// update agent data every frame, include the position info of agent
// and animation info of agent
void CFireBall::UpdateData()
{
	fcout << "CFireBall::UpdateData()" << std::endl;
	// manipulate the index of animation
	++m_curSpriteIndex;
	if(m_curSpriteIndex > m_StateSpriteNumMap[m_eCurBallStateID] - 1) // index num is 0..N-1
		m_curSpriteIndex = 0;

	// manipulate the position of animation
	//m_curPos_x += 15;	// just move forward
	m_pCurState -> MovingStrategy(this);
	if(m_curPos_x >= WND_WIDTH - 20)		m_curPos_x = WND_WIDTH - 20;
	if(m_curPos_x <= 0)	m_curPos_x = -20;

	fcout << "Ball state: " << m_StateNameMap[m_eCurBallStateID].c_str() << std::endl;
	fcout << "Ball positon x: " << m_curPos_x << "\ty: " << m_curPos_y << std::endl;
}
// update agent state every frame
void CFireBall::UpdateState()
{
	fcout << "CFireBall::UpdateState()" << std::endl;
	m_pCurState->ExecuteState(this);
}
// init agent called by upper(referenced) calss
bool CFireBall::InitAgent(CGraphics* pGraphic)
{
	this->LoadSprite(pGraphic);
	return true;
}	
void CFireBall::ChangeState(CState<CFireBall>* pNewState)
{}

void CFireBall::SetPosX(int x)
{
	m_curPos_x = x;
}

void CFireBall::SetPosY(int y)
{
	m_curPos_y = y;
}
bool CFireBall::HasFireEnd()
{
	return m_FireFinished;
}
void CFireBall::FireEnd(bool yes)
{
	m_FireFinished = yes;
}

// to check whether this frame has finished
bool CFireBall::HasFrameFinished()
{
	return ((m_curSpriteIndex + 1) == m_StateSpriteNumMap[m_eCurBallStateID]);
}
// fire to which direction
void CFireBall::SetFireDirection(bool reverse)
{
	m_ReverseFlag = reverse;
}
bool CFireBall::GetFireDirection()
{
	return m_ReverseFlag;
}