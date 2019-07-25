#include "stdafx.h"
#include "MidBoss.h"
#include "MonBullet.h"


CMidBoss::CMidBoss()
	:m_fCoolDown2(1.f), m_iShotCount(0)
{
	//��� ���ӿ�����Ʈ�� ������ ������Ʈ ���� ����Ʈ�� �����͸� �����Ѵ�.
	m_ObjLst[OBJECT_MONSTER].push_back(this);
}


CMidBoss::~CMidBoss()
{
	Release();
}

void CMidBoss::Initialize()
{
	switch (m_iMonType)
	{
	case 0:
		m_tInfo.fX = WINCX / 2.f;
		m_tInfo.fY = 200.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 50.f;

		m_fCoolDown = 1.f;

		m_pTexture = CResourceMgr::LoadTexture("Monster", _T("Stage/Monster/BigAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(255, 255, 255));
		break;
	}

}

int CMidBoss::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	m_fCoolDown -= DELTA_TIME;

	// �ѿ� ��ġ. ������ �Լ��� �� �� ����.
	m_Barrel.x = m_tInfo.fX + 85.f;
	m_Barrel.y = m_tInfo.fY + 30.f;

	// 2���ѿ�
	m_Barrel2.x = m_tInfo.fX -85.f;
	m_Barrel2.y = m_tInfo.fY + 30.f;

	IsMoving();
	IsOutRange();
	IsFire();
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(300.f, 300.f);

	return NO_EVENT;
}

void CMidBoss::Release()
{
	m_pTexture->SafeDelete();

	// ������ ����Ʈ���� ������Ʈ�� ����
	OBJLIST::iterator iter_find = find(m_ObjLst[OBJECT_MONSTER].begin(), m_ObjLst[OBJECT_MONSTER].end(), this);
	if (iter_find != m_ObjLst[OBJECT_MONSTER].end())
	{
		m_ObjLst[OBJECT_MONSTER].erase(iter_find);
	}

}

void CMidBoss::IsMoving()
{
	switch (m_iMonType)
	{
	case 0:
		// �����̵�
		// ���� �̵����� �Է� ����
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	}

}

void CMidBoss::IsFire()
{
	if (m_fCoolDown < 0)
	{
		//m_fCoolDown2 -= DELTA_TIME;

		// ��ٿ��� 0�ʰ� �Ǿ��� �� ���� 5���縦 �ϵ���
		if (true)
		{
			m_fAngle = GetAngle(m_pPlayerLst->front(), &m_Barrel);
			CGameObject* pBullet1 = new CMonBullet;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			dynamic_cast<CMonBullet*>(pBullet1)->SetAngle(m_fAngle);
			m_pBulletLst->push_back(pBullet1);

			m_fAngle = GetAngle(m_pPlayerLst->front(), &m_Barrel2);
			CGameObject* pBullet2 = new CMonBullet;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_pBulletLst->push_back(pBullet2);
			dynamic_cast<CMonBullet*>(pBullet2)->SetAngle(m_fAngle);

			//m_fCoolDown2 += 1.f;
			++m_iShotCount;
		}

		if (m_iShotCount > 5)
		{
			m_fCoolDown += 3.f;
			m_iShotCount = 0;
		}
	}


}
