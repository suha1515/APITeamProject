#include "stdafx.h"
#include "WingMan.h"
#include "Bullet.h"


CWingMan::CWingMan()
{
	m_tInfo.fCX = 10;
	m_tInfo.fCY = 10;
	m_tInfo.fSpeed = 400.f;
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Helper", _T("Stage/Player/Helper.bmp"));
	m_pTexture->SetColorKey(RGB(0, 128, 128));

	m_pAnimator = new CAnimator;
	m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 0, 0, 2, 1, 0.f, 1.f);
}
CWingMan::~CWingMan()
{

}

void CWingMan::Initialize()
{

}

int CWingMan::Update()
{
	
	Move();

	CGameObject::UpdateRect();
	//CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 3.f,3.f*(16.f / 13.f));

	CGameObject::UpdateImgInfo(30.f, 35.f, 1.f, 1.f);
	return NO_EVENT;
}

void CWingMan::Render(HDC hDC)
{
	//m_pTexture->DrawTexture(hDC, m_tImgInfo);
	m_pAnimator->RunAnim(0, hDC, m_tImgInfo);
	//Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY - m_tInfo.fCY, m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY + m_tInfo.fCY);
}

void CWingMan::Fire()
{
	CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET,CreateBullet());
}

void CWingMan::Move()
{

	float dist = Distance(m_tInfo.fX, m_tInfo.fY, (*m_Location).x, (*m_Location).y);
	
	if (dist > 20)
	{
		float fx = (*m_Location).x - m_tInfo.fX;
		float fy = (*m_Location).y - m_tInfo.fY;


		float angle = GetAngle(fx, fy);

		m_tInfo.fX += cosf(angle)*DELTA_TIME*m_tInfo.fSpeed;
		m_tInfo.fY += sinf(angle)*DELTA_TIME*m_tInfo.fSpeed;
	}
	  /*m_tInfo.fX = (*m_Location).x;
		m_tInfo.fY = (*m_Location).y;*/
	
}

void CWingMan::SetLocation(POINT* pt)
{
	m_Location = pt;
}

void CWingMan::Release()
{
	m_pTexture->SafeDelete();
}

CGameObject * CWingMan::CreateBullet()
{
	return CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY-20);
}
