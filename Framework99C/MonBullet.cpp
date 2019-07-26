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
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_pAnimator = new CAnimator;

	switch (m_BulletType)
	{
	case SMALL:
		m_tInfo.fSpeed = 10.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MonBullet1", _T("Stage/Bullet/MBasic_Bullet.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 8, 1, 0, 0, 7, 0, 1.5f);
		break;
	case MIDIUM:
		m_tInfo.fSpeed = 5.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MonBullet2", _T("Stage/Bullet/Magic_Elec.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 3, 1, 0, 0, 2, 0, 0.1f);
		break;
	case FAST:
		m_tInfo.fSpeed = 15.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MonBullet3", _T("Stage/Bullet/MBasic_Bullet2.bmp"));
		m_pTexture->SetColorKey(RGB(0, 0, 0));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 4, 1, 0, 0, 3, 0, 0.1f);
		break;
	case BOMB:
		m_tInfo.fSpeed = 3.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MonBullet4", _T("Stage/Bullet/Magic_Elec.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 3, 1, 0, 0, 2, 0, 0.1f);
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
	switch (m_BulletType)
	{
	case 0:
		CGameObject::UpdateImgInfo(20, 20);
		m_pAnimator->AnimateClip(0, hDC, m_tImgInfo);
		break;
	case 1:
		CGameObject::UpdateImgInfo(20, 20);
		m_pAnimator->AnimateClip(0, hDC, m_tImgInfo);
		break;
	case 2:
		CGameObject::UpdateImgInfo(20 * 1.5f, 20 * 1.5f);
		m_pAnimator->AnimateClip(0, hDC, m_tImgInfo);
		break;
	case 3:
		CGameObject::UpdateImgInfo(20 * 2.f, 20 * 2.f);
		m_pAnimator->AnimateClip(0, hDC, m_tImgInfo);
		break;
	}
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
			dynamic_cast<CMonBullet*>(pBullet)->SetInfo(MIDIUM, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet);

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 45.f;
			dynamic_cast<CMonBullet*>(pBullet2)->SetInfo(MIDIUM, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet2)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			CGameObject* pBullet3;
			pBullet3 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 90.f;
			dynamic_cast<CMonBullet*>(pBullet3)->SetInfo(MIDIUM, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet3)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet3);

			CGameObject* pBullet4;
			pBullet4 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 135.f;
			dynamic_cast<CMonBullet*>(pBullet4)->SetInfo(MIDIUM, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet4)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet4);

			CGameObject* pBullet5;
			pBullet5 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 180.f;
			dynamic_cast<CMonBullet*>(pBullet5)->SetInfo(MIDIUM, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet5)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet5);

			CGameObject* pBullet6;
			pBullet6 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 225.f;
			dynamic_cast<CMonBullet*>(pBullet6)->SetInfo(MIDIUM, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet6)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet6);

			CGameObject* pBullet7;
			pBullet7 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 270.f;
			dynamic_cast<CMonBullet*>(pBullet7)->SetInfo(MIDIUM, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet7)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet7);

			CGameObject* pBullet8;
			pBullet8 = CAbstractFactory<CMonBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
			m_fAngle = 315.f;
			dynamic_cast<CMonBullet*>(pBullet8)->SetInfo(MIDIUM, m_fAngle);
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
