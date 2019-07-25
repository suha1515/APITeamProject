#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
	:m_iMonType(0)
{

}


CMonster::~CMonster()
{
	//Release();
}

void CMonster::Initialize()
{
	m_tInfo.fX = WINCX/2.f;
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;


	m_tInfo.fSpeed = 300.f;

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
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

float CMonster::GetAngle(CGameObject* pDesObj, CGameObject* pSrcObj)
{
	float fAngle = atan2(pDesObj->GetInfo().fY - pSrcObj->GetInfo().fY, pDesObj->GetInfo().fX - pSrcObj->GetInfo().fX) * 180 / PI;
	if (fAngle < 0)
		fAngle += 360;

	return fAngle;
}

float CMonster::GetAngle(CGameObject* pDesObj, POINT* pPoint)
{
	float fAngle = atan2(pDesObj->GetInfo().fY - pPoint->y, pDesObj->GetInfo().fX - pPoint->x) * 180 / PI;
	if (fAngle < 0)
		fAngle += 360;

	return fAngle;
}

void CMonster::SetDamaged(int dmg)
{
	m_iHP -= dmg;

	if (m_iHP <= 0)
	{
		m_bIsDead = true;
	}

}

void CMonster::SetBulletLst(OBJLIST * pBulletLst)
{
	m_pBulletLst = pBulletLst;
}

void CMonster::SetPlayer(CGameObject * pPlayer)
{
	m_pPlayer = pPlayer;
}

void CMonster::SetMonType(int iType)
{
	m_iMonType = iType;
}

void CMonster::IsMoving()
{
	m_tInfo.fX += m_tInfo.fSpeed  * DELTA_TIME;
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
		m_tInfo.fSpeed *= -1;
}

void CMonster::IsFire()
{
}
