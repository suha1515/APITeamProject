#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
{

}


CStage::~CStage()
{
}

void CStage::Initialize()
{
	m_tInfo.fX = 0;
	//m_tInfo.fY = 8030.f - WINCY;
	m_tInfo.fY = 2530.f - WINCY;
	m_tInfo.fCX = 700.f;
	m_tInfo.fCY = 8030.f;
	CGameManager::GetInstance()->SetStageProgress(m_tInfo.fY);
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Stage_1", _T("Stage/StageBack/Stage_1.bmp"));
	m_pTexture->SetKeyEnable(false);
}

int CStage::Update()
{
	if (0 < m_tInfo.fY)
	{
		m_tInfo.fY -= STAGE_SPEED * DELTA_TIME;	// 보스전 진입시 속도를 늦추도록.
		CGameManager::GetInstance()->SetStageProgress(m_tInfo.fY);
	}
	CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY);
	
	return NO_EVENT;
}

void CStage::Render(HDC hDC)
{
	m_pTexture->DrawTexture(hDC, m_tImgInfo);
}

void CStage::Release()
{
	m_pTexture->SafeDelete();
}
