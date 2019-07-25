#include "stdafx.h"
#include "WingMan.h"
#include "Bullet.h"


CWingMan::CWingMan()
{
	m_tInfo.fCX = 10;
	m_tInfo.fCY = 10;
	m_tInfo.fSpeed = 350.f;
}
CWingMan::~CWingMan()
{

}

void CWingMan::Initialize()
{
}

int CWingMan::Update()
{
	CGameObject::UpdateRect();
	Move();
	return NO_EVENT;
}

void CWingMan::Render(HDC hDC)
{
	Rectangle(hDC, m_tInfo.fX - m_tInfo.fCX, m_tInfo.fY - m_tInfo.fCY, m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY + m_tInfo.fCY);
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
}

CGameObject * CWingMan::CreateBullet()
{
	return CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
}
