#include "stdafx.h"
#include "MonBullet.h"


CMonBullet::CMonBullet()
	:m_iDmg(1)
{
	//모든 게임오브젝트는 생성시 오브젝트 관리 리스트에 포인터를 전달한다.
	m_ObjLst[OBJECT_MONBULLET].push_back(this);
}


CMonBullet::~CMonBullet()
{
	Release();
}

void CMonBullet::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_tInfo.fSpeed = 10.f;

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Bullet", _T("Stage/Bullet/Magic_Elec3.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));

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
	OBJLIST::iterator iter_find = find(m_ObjLst[OBJECT_MONBULLET].begin(), m_ObjLst[OBJECT_MONBULLET].end(), this);
	if (iter_find != m_ObjLst[OBJECT_MONBULLET].end())
	{
		m_ObjLst[OBJECT_MONBULLET].erase(iter_find);
	}

}

void CMonBullet::SetAngle(float fAngle)
{
	m_fAngle = fAngle;
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
	// 일반탄: 플레이어의 방향으로 직선이동
	m_tInfo.fX += m_tInfo.fSpeed * cosf(m_fAngle * PI / 180);
	m_tInfo.fY += m_tInfo.fSpeed * sinf(m_fAngle * PI / 180);
}
