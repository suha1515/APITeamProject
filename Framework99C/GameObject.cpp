#include "stdafx.h"
#include "GameObject.h"

CGameObject::CGameObject()
	:  m_bIsDead(false)
{
}


CGameObject::~CGameObject()
{
}

const INFO & CGameObject::GetInfo() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tInfo;
}

const RECT & CGameObject::GetRect() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tRect;
}

const bool CGameObject::GetDead() const
{

	return m_bIsDead;
}

void CGameObject::SetPos(float x, float y)
{
	m_tInfo.fX = x;
	m_tInfo.fY = y;
}

void CGameObject::SetDead(bool bIsDead)
{
	m_bIsDead = bIsDead;
}

void CGameObject::UpdateRect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.fX - m_tInfo.fCX * 0.5f);
	m_tRect.top = static_cast<LONG>(m_tInfo.fY - m_tInfo.fCY * 0.5f);
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + m_tInfo.fCX * 0.5f);
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + m_tInfo.fCY * 0.5f);
}

void CGameObject::UpdateImgInfo(float CImgX, float CImgY)
{
	m_tImgInfo.fX = m_tInfo.fX;
	m_tImgInfo.fY = m_tInfo.fY;
	m_tImgInfo.fImgCX = CImgX;
	m_tImgInfo.fImgCY = CImgY;
	m_tImgInfo.fPivotX = (m_tInfo.fX - m_tRect.left) / m_tInfo.fCX;
	m_tImgInfo.fPivotY = (m_tInfo.fY - m_tRect.top) / m_tInfo.fCY;
	m_tImgInfo.fScaleX = 1.f;
	m_tImgInfo.fScaleY = 1.f;
}

void CGameObject::UpdateImgInfo(float CImgX, float CImgY, float scaleX, float scaleY)
{
	UpdateImgInfo(CImgY, CImgY);
	m_tImgInfo.fScaleX = scaleX;
	m_tImgInfo.fScaleY = scaleY;
}
