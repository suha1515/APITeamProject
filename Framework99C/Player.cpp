#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::SetBulletLst(OBJLIST* pBulletLst)
{
	m_pBulletLst = pBulletLst;
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 10.f;
}

int CPlayer::Update()
{
	KeyInput();

	return NO_EVENT;
}

void CPlayer::Render(HDC hDC)
{
	CGameObject::UpdateRect();
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

CGameObject* CPlayer::CreateBullet()
{
	return CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
}

CGameObject* CPlayer::CreateBullet(BULLET_DIRECTION eDir)
{
	CGameObject* pBullet = CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pBullet)->SetDirection(eDir);

	return pBullet;
}

void CPlayer::KeyInput()
{
	//플레이어 영역 제한 버벅거리는거 없음.
	if (m_tRect.left > 0)
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			m_tInfo.fX -= m_fSpeed;
	}
	if (m_tRect.right < WINCX)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			m_tInfo.fX += m_fSpeed;
	}
	if (m_tRect.top > 0)
	{
		if (GetAsyncKeyState(VK_UP) & 0x8000)
			m_tInfo.fY -= m_fSpeed;
	}
	if (m_tRect.bottom < WINCX)
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState('W') & 0x8000)
		m_pBulletLst->push_back(CreateBullet(BULLET_UP));
	if (GetAsyncKeyState('S') & 0x8000)
		m_pBulletLst->push_back(CreateBullet(BULLET_DOWN));
	if (GetAsyncKeyState('A') & 0x8000)
		m_pBulletLst->push_back(CreateBullet(BULLET_LEFT));
	if (GetAsyncKeyState('D') & 0x8000)
		m_pBulletLst->push_back(CreateBullet(BULLET_RIGHT));
}
