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
	m_tInfo.fY = 8030.f - WINCY;
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Stage_1", _T("Stage/StageBack/Stage_1.bmp"));
	m_pTexture->SetKeyEnable(false);
}

int CStage::Update()
{
	if (0 < m_tInfo.fY)
	{
		m_tInfo.fY -= 100.f * DELTA_TIME;
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
