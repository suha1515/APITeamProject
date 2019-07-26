#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDirection(BULLET_UP)
{
}


CBullet::~CBullet()
{
	//Release();
}

void CBullet::SetDirection(BULLET_DIRECTION eDir)
{
	m_eDirection = eDir;
}

void CBullet::SetBulletType(PLAYER_BULLET_TYPE type)
{
	m_BulletType = type;
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_tInfo.fSpeed = 600.f;

	m_pAnimator = new CAnimator;

	if (m_BulletType == PLAYER_BULLET_TYPE::LEVEL1)
	{
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet_LEVEL1", _T("Stage/Bullet/Bullet_Eg_a.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
	}
	else if (m_BulletType == PLAYER_BULLET_TYPE::LEVEL2)
	{
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet_LEVEL2", _T("Stage/Bullet/Bullet_Eg_b.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
	}
	else if (m_BulletType == PLAYER_BULLET_TYPE::LEVEL3)
	{
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet_LEVEL3", _T("Stage/Bullet/Bullet_Eg_c.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
	}
	else if (m_BulletType == PLAYER_BULLET_TYPE::LEVEL4)
	{
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet_LEVEL4", _T("Stage/Bullet/Bullet_Eg_d.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
	}
	else if (m_BulletType == PLAYER_BULLET_TYPE::WINGMAN)
	{
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet_WINGMAN", _T("Stage/Bullet/Bullet_Explo.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 3, 1, 0, 0, 2, 0, 1.0f);
	}

	
}

int CBullet::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	IsMoving();
	IsOutRange();	
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(m_tInfo.fCX*4 , m_tInfo.fCY*5 );
	return NO_EVENT;
}

void CBullet::Render(HDC hDC)
{
	if (m_BulletType == PLAYER_BULLET_TYPE::WINGMAN)
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 3.f, 4.f);
		m_pAnimator->RunAnim(0, hDC, m_tImgInfo);
	}
	else
	{
		m_pTexture->DrawTexture(hDC, m_tImgInfo);
	}
	
	
}

void CBullet::Release()
{
	m_pTexture->SafeDelete();
}

void CBullet::IsMoving()
{
	switch (m_eDirection)
	{
	case BULLET_LEFT:
		m_tInfo.fX -= m_tInfo.fSpeed  * DELTA_TIME;
		break;
	case BULLET_RIGHT:
		m_tInfo.fX += m_tInfo.fSpeed  * DELTA_TIME;
		break;
	case BULLET_UP:
		m_tInfo.fY -= m_tInfo.fSpeed  * DELTA_TIME;
		break;
	case BULLET_DOWN:
		break;
	}
}

void CBullet::IsOutRange()
{
	CGameObject::UpdateRect();

	if (0 >= m_tRect.left || 0 >= m_tRect.top
		|| WINCX <= m_tRect.right || WINCY <= m_tRect.bottom)
	{
		m_bIsDead = true;
		//Release();
	}
		
}
