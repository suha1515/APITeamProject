#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
	:m_pTexture(nullptr)
{
}


CStage::~CStage()
{
}

void CStage::Initialize()
{
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 8030.f - WINCY;
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	m_pTexture = new CTexture;
	m_pTexture->SetPivot(m_tInfo);
	m_pTexture->SetTexture(hInst, _T("./Texture/Stage/StageBack/"), _T("Stage_1.bmp"));
}

int CStage::Update()
{
	if (0 < m_tInfo.fY)
	{
		m_tInfo.fY -= 100.f * DELTA_TIME;
		m_pTexture->SetPivot(m_tInfo);
	}
	
	return NO_EVENT;
}

void CStage::Render(HDC hDC)
{
	/*BitBlt(hDC, 0, 0, WINCX, WINCY, m_pTexture->GetDC(), 0, m_tInfo.fY, SRCCOPY);*/
	m_pTexture->Render(hDC);
}

void CStage::Release()
{
}
