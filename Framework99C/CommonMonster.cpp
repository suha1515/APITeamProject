#include "stdafx.h"
#include "CommonMonster.h"
#include "MonBullet.h"


CCommonMonster::CCommonMonster()
{
	//��� ���ӿ�����Ʈ�� ������ ������Ʈ ���� ����Ʈ�� �����͸� �����Ѵ�.
	m_ObjLst[OBJECT_MONSTER].push_back(this);
}


CCommonMonster::~CCommonMonster()
{
	Release();
}

void CCommonMonster::Initialize()
{
	switch (m_iMonType)
	{
	case 0:
		// �Լ��� �ϳ� ���� ���� �ִ� �͵� ������.
		m_tInfo.fX = WINCX / 2.f;
		m_tInfo.fY = 200.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 80.f;

		m_fCoolDown = 2.f;

		m_pTexture = CResourceMgr::LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		break;
	}

}

int CCommonMonster::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	m_fCoolDown -= DELTA_TIME;

	// �ѿ� ��ġ. ������ �Լ��� �� �� ����.
	m_Barrel.x = m_tInfo.fX;
	m_Barrel.y = m_tInfo.fY + 100.f;

	IsMoving();
	IsOutRange();
	IsFire();
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(300.f, 300.f);

	return NO_EVENT;
}

void CCommonMonster::Release()
{
	m_pTexture->SafeDelete();

	// ������ ����Ʈ���� ������Ʈ�� ����
	OBJLIST::iterator iter_find = find(m_ObjLst[OBJECT_MONSTER].begin(), m_ObjLst[OBJECT_MONSTER].end(), this);
	if (iter_find != m_ObjLst[OBJECT_MONSTER].end())
	{
		m_ObjLst[OBJECT_MONSTER].erase(iter_find);
	}

}

void CCommonMonster::IsMoving()
{
	switch (m_iMonType)
	{
	case 0:
		// �����̵�
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	}
}

void CCommonMonster::IsFire()
{
	switch (m_iMonType)
	{
	case 0:
		if (m_fCoolDown < 0)
		{
			CGameObject* pObject = new CMonBullet;
			pObject = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);

			m_fAngle = GetAngle(m_pPlayerLst->front(), &m_Barrel);

			dynamic_cast<CMonBullet*>(pObject)->SetAngle(m_fAngle);
			m_pBulletLst->push_back(pObject);


			m_fCoolDown += 2.f;
		}

		break;
	}

}

