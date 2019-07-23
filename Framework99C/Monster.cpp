#include "stdafx.h"
#include "Monster.h"


CMonster::CMonster()
{
	//모든 게임오브젝트는 생성시 오브젝트 관리 리스트에 포인터를 전달한다.
	m_ObjLst[OBJECT_MONSTER].push_back(this);
}


CMonster::~CMonster()
{
	//Release();
}

void CMonster::Initialize()
{
	m_tInfo.fX = WINCX/2.f;
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;


	m_tInfo.fSpeed = 300.f;

	m_pTexture = CResourceMgr::LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
}

int CMonster::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	IsMoving();
	IsOutRange();
	CGameObject::UpdateRect();

	return NO_EVENT;
}

void CMonster::Render(HDC hDC)
{
	m_pTexture->Render(hDC);
	TransparentBlt(hDC, m_tInfo.fX - (354 /2), m_tInfo.fY - (372 / 2), 354, 372, m_pTexture->GetDC(), 0, 0, 116, 122, RGB(0, 128, 128));
}

void CMonster::Release()
{
	// 삭제시 리스트에서 오브젝트를 삭제
	OBJLIST::iterator iter_find = find(m_ObjLst[OBJECT_MONSTER].begin(), m_ObjLst[OBJECT_MONSTER].end(), this);
	if (iter_find != m_ObjLst[OBJECT_MONSTER].end())
	{
		m_ObjLst[OBJECT_MONSTER].erase(iter_find);
	}
}

void CMonster::IsMoving()
{
	m_tInfo.fX += m_tInfo.fSpeed  * DELTA_TIME;
	CGameObject::UpdateRect();

	if (m_tRect.left < 0.f)
		m_tInfo.fX += 0.f - m_tRect.left;
	else if(m_tRect.right > WINCX)
		m_tInfo.fX -= m_tRect.right - WINCX;

	CGameObject::UpdateRect();

}

void CMonster::IsOutRange()
{
	CGameObject::UpdateRect();

	if (0.f >= m_tRect.left || WINCX <= m_tRect.right)
		m_tInfo.fSpeed *= -1;
}
