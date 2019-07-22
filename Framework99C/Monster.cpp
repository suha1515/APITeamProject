#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	m_tInfo.fX = WINCX/2.f;
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 0.f;
	m_pTexture = CResourceMgr::LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
	m_pTexture->SetColorKey(RGB(0, 128, 128));
}

int CMonster::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	IsMoving();
	IsOutRange();
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(300.f, 300.f);

	return NO_EVENT;
}

void CMonster::Render(HDC hDC)
{
	m_pTexture->DrawTexture(hDC, m_tImgInfo);
}

void CMonster::Release()
{
	m_pTexture->SafeDelete();
}

void CMonster::IsMoving()
{
	m_tInfo.fX += m_fSpeed * DELTA_TIME;
	CGameObject::UpdateRect();

	if (m_tRect.left < 0.f)
		m_tInfo.fX += 0.f - m_tRect.left;
	else if(m_tRect.right > WINCX)
		m_tInfo.fX -= m_tRect.right - WINCX;

	CGameObject::UpdateRect();

}

void CMonster::IsOutRange()
{
	CGameObject::UpdateRect();

	if (0.f >= m_tRect.left || WINCX <= m_tRect.right)
		m_fSpeed *= -1;
}
