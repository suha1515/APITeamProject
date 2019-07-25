#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
	: m_eDirection(BULLET_UP)
{
	//모든 게임오브젝트는 생성시 오브젝트 관리 리스트에 포인터를 전달한다.
	m_ObjLst[OBJLECT_BULLET].push_back(this);
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::SetDirection(BULLET_DIRECTION eDir)
{
	m_eDirection = eDir;
}

void CBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_tInfo.fSpeed = 600.f;

	m_pTexture = CResourceMgr::LoadTexture("Bullet", _T("Stage/Bullet/Bullet_Eg_a.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
}

int CBullet::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	IsMoving();
	IsOutRange();	
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(m_tInfo.fCX * 6, m_tInfo.fCY * 10);
	return NO_EVENT;
}

void CBullet::Render(HDC hDC)
{
	m_pTexture->DrawTexture(hDC, m_tImgInfo);
}

void CBullet::Release()
{
	m_pTexture->SafeDelete();
	// 삭제시 리스트에서 오브젝트를 삭제
	OBJLIST::iterator iter_find = find(m_ObjLst[OBJLECT_BULLET].begin(), m_ObjLst[OBJLECT_BULLET].end(), this);
	if (iter_find != m_ObjLst[OBJLECT_BULLET].end())
	{
		m_ObjLst[OBJLECT_BULLET].erase(iter_find);
	}
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
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		break;
	}
}

void CBullet::IsOutRange()
{
	CGameObject::UpdateRect();

	if (0 >= m_tRect.left || 0 >= m_tRect.top
		|| WINCX <= m_tRect.right || WINCY <= m_tRect.bottom)
		m_bIsDead = true;
}
