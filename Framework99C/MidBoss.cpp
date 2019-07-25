#include "stdafx.h"
#include "MidBoss.h"
#include "MonBullet.h"

CMidBoss::CMidBoss()
	:m_fAngle2(0.f)
{
}


CMidBoss::~CMidBoss()
{
	Release();
}

void CMidBoss::Initialize()
{
	m_iShotCount = 0;

	switch (m_iMonType)
	{
	case 0:
		m_tInfo.fX = WINCX / 2.f;
		m_tInfo.fY = 200.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 50.f;

		m_fCoolDown = 2.f;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		break;
	case 1:
		m_tInfo.fX = WINCX / 2.f;
		m_tInfo.fY = 200.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 50.f;

		m_fCoolDown = 2.f;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		break;
	case 2:
		m_tInfo.fX = WINCX / 2.f;
		m_tInfo.fY = 200.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 50.f;

		m_fCoolDown = 4.f;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		break;

	}

}

int CMidBoss::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;
	switch (m_iMonType)
	{
	case 0:
		SetBarrel(&m_Barrel, 85.f, 30.f);
		SetBarrel(&m_Barrel2, -85.f, 30.f);
		break;

	case 1:
		SetBarrel(&m_Barrel, 85.f, 30.f);
		SetBarrel(&m_Barrel2, -85.f, 30.f);
		SetBarrel(&m_Barrel3, 85.f, 0.f);
		SetBarrel(&m_Barrel4, -85.f, 0.f);
		break;
	case 2:
		SetBarrel(&m_Barrel, 85.f, 30.f);
		SetBarrel(&m_Barrel2, -85.f, 30.f);

		if (nullptr == m_pTarget)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) - 20.f;
			m_fAngle2 = GetAngle(m_pTarget, &m_Barrel) + 20.f;

		}

		break;
	}

	IsMoving();
	IsOutRange();
	IsFire();
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(300.f, 300.f);

	return NO_EVENT;
}

void CMidBoss::Release()
{
	m_pTexture->SafeDelete();
}

void CMidBoss::IsMoving()
{
	switch (m_iMonType)
	{
	case 0:
		// 하향이동
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	case 1:
		// 하향이동
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	case 2:
		// 하향이동
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	}

}

void CMidBoss::IsFire()
{
	if (m_fCoolDown >= 0)
		m_fCoolDown -= DELTA_TIME;

	switch (m_iMonType)
	{
	case 0:
		// 쌍발 6연사
		if (m_fCoolDown < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pBullet1)->SetAngle(m_fAngle);
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel2);
			dynamic_cast<CMonBullet*>(pBullet2)->SetAngle(m_fAngle);
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			m_fCoolDown += 0.1f;
			++m_iShotCount;
		}
		if (m_iShotCount > 5)
		{
			m_fCoolDown += 3.0f;
			m_iShotCount = 0;
		}
		break;
	case 1:
		// 3갈래 공격 * 2
		if (m_fCoolDown < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pBullet1)->SetAngle(m_fAngle);
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) + 10.f;
			dynamic_cast<CMonBullet*>(pBullet2)->SetAngle(m_fAngle);
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			CGameObject* pBullet3;
			pBullet3 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) - 10.f;
			dynamic_cast<CMonBullet*>(pBullet3)->SetAngle(m_fAngle);
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet3);

			// 위의 코드 복붙해서 숫자 바꾸고 배럴2로 적용하면 된다.

			m_fCoolDown += 0.1f;
			++m_iShotCount;
		}
		if (m_iShotCount > 2)
		{
			m_fCoolDown += 3.0f;
			m_iShotCount = 0;
		}
		break;
	case 2:
		// 회전난사
		if (m_fCoolDown < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			dynamic_cast<CMonBullet*>(pBullet1)->SetAngle(m_fAngle);
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);

			m_fAngle += 5.f;

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			dynamic_cast<CMonBullet*>(pBullet2)->SetAngle(m_fAngle2);
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			m_fAngle2 -= 5.f;

			m_fCoolDown += 0.05f;
			++m_iShotCount;
		}
		if (m_iShotCount > 10)
		{
			m_fCoolDown += 2.0f;
			m_iShotCount = 0;
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) - 10.f;
			m_fAngle2 = GetAngle(m_pTarget, &m_Barrel) + 10.f;
		}

		break;
	}

}
