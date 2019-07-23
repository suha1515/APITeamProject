#include "stdafx.h"
#include "Stage.h"


CStage::CStage()
{
	m_ObjLst[OBJECT_STAGE].push_back(this);
}


CStage::~CStage()
{
}

void CStage::Initialize()
{
	m_tInfo.fX = WINCX;
	m_tInfo.fY = 8030.f - WINCY;
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;

	CGameObject::UpdateRect();
	m_pTexture = CResourceMgr::LoadTexture("Stage_1", _T("Stage/StageBack/Stage_1.bmp"));
}

int CStage::Update()
{
	if (0 < m_tInfo.fY)
	{
		m_tInfo.fY -= 100.f * DELTA_TIME;
	}
	CGameObject::UpdateRect();
	
	return NO_EVENT;
}

void CStage::Render(HDC hDC)
{
	m_pTexture->Render(hDC);
	BitBlt(hDC, 0, 0, WINCX, WINCY, m_pTexture->GetDC(), 0, m_tInfo.fY, SRCCOPY);
}

void CStage::Release()
{
	OBJLIST::iterator iter_find = find(m_ObjLst[OBJECT_STAGE].begin(), m_ObjLst[OBJECT_STAGE].end(), this);
	if (iter_find != m_ObjLst[OBJECT_STAGE].end())
	{
		m_ObjLst[OBJECT_STAGE].erase(iter_find);
	}
}
