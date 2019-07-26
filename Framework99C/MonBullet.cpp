#include "stdafx.h"
#include "MonBullet.h"

// 몬스터 탄환
/*
0.일반탄
1.저속탄
2.고속탄
3.산탄
*/

CMonBullet::CMonBullet()
	:m_iDmg(1), m_fFuse(2.f)
{

}


CMonBullet::~CMonBullet()
{
	Release();
}

void CMonBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	switch (m_BulletType)
	{
	case SMALL:
		m_tInfo.fSpeed = 10.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet", _T("Stage/Bullet/Magic_Elec3.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		break;
	case MIDIUM:
		m_tInfo.fSpeed = 5.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet", _T("Stage/Bullet/Magic_Elec3.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		break;
	case FAST:
		m_tInfo.fSpeed = 15.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet", _T("Stage/Bullet/Bullet_Mob_D.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		break;
	case BOMB:
		m_tInfo.fSpeed = 3.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet", _T("Stage/Bullet/Bullet_Mob_D.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		break;
	}

}

int CMonBullet::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	IsMoving();
	IsOutRange();
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(m_tInfo.fCX * 1, m_tInfo.fCY * 1);
	return NO_EVENT;
}

void CMonBullet::Render(HDC hDC)
{
	m_pTexture->DrawTexture(hDC, m_tImgInfo);
}

void CMonBullet::Release()
{
	m_pTexture->SafeDelete();
	// 삭제시 리스트에서 오브젝트를 삭제
}

void CMonBullet::SetInfo(BULLET_TYPE bType, float fAngle)
{
	m_fAngle = fAngle;
	m_BulletType = bType;
}

void CMonBullet::IsOutRange()
{
	CGameObject::UpdateRect();

	if (0 >= m_tRect.left || 0 >= m_tRect.top
		|| WINCX <= m_tRect.right || WINCY <= m_tRect.bottom)
		m_bIsDead = true;

}

void CMonBullet::IsMoving()
{
	if (m_fFuse >= 0)
		m_fFuse -= DELTA_TIME;

	switch (m_BulletType)
	{
	case BOMB:
		// 일정거리 비행하다 산탄
		if (m_fFuse < 0)
		{
			m_bIsDead = true;

			CGameObject* pBullet;
			pBullet = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 0.f;
			dynamic_cast<CMonBullet*>(pBullet)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet);

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 45.f;
			dynamic_cast<CMonBullet*>(pBullet2)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet2)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			CGameObject* pBullet3;
			pBullet3 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 90.f;
			dynamic_cast<CMonBullet*>(pBullet3)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet3)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet3);

			CGameObject* pBullet4;
			pBullet4 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 135.f;
			dynamic_cast<CMonBullet*>(pBullet4)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet4)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet4);

			CGameObject* pBullet5;
			pBullet5 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 180.f;
			dynamic_cast<CMonBullet*>(pBullet5)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet5)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet5);

			CGameObject* pBullet6;
			pBullet6 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 225.f;
			dynamic_cast<CMonBullet*>(pBullet6)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet6)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet6);

			CGameObject* pBullet7;
			pBullet7 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 270.f;
			dynamic_cast<CMonBullet*>(pBullet7)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet7)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet7);

			CGameObject* pBullet8;
			pBullet8 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 315.f;
			dynamic_cast<CMonBullet*>(pBullet8)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet8)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet8);

		}
		else
		{
			m_tInfo.fX += m_tInfo.fSpeed * cosf(m_fAngle * PI / 180);
			m_tInfo.fY += m_tInfo.fSpeed * sinf(m_fAngle * PI / 180);
		}

		break;
	default:
		//플레이어의 방향으로 직선이동
		m_tInfo.fX += m_tInfo.fSpeed * cosf(m_fAngle * PI / 180);
		m_tInfo.fY += m_tInfo.fSpeed * sinf(m_fAngle * PI / 180);

	}
}
