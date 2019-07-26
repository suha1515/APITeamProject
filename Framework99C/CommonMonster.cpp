#include "stdafx.h"
#include "CommonMonster.h"
#include "MonBullet.h"

// ���Ÿ��(Ÿ�Լ����� ���� ������)
/*
MonType 0~3

�̵����
0.���������̵�
1.�����������̵�(60��)
2.�����������̵�(60��)
3.�÷��̾��� ��ġ�� �����ϸ� �����̵�

��ݹ��(��ٿ�)
0.�ܹ߻��(2��)
1.����(0.2��)
2.�ֹ�(2��)
*/

CCommonMonster::CCommonMonster()
{
}


CCommonMonster::~CCommonMonster()
{
	Release();
}

void CCommonMonster::Initialize()
{
	// �������
	// ���͸��� ũ�Ⱑ �ٸ� ��� ũ�Ⱚ�� ������ �־��ش�.
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_iShotCount = 0;
	m_pAnimator = new CAnimator;

	switch (m_Various)
	{
	case 0:
		m_tInfo.fSpeed = 300.f;
		m_iHP = 1;

		m_fCoolDown = 1.f;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster1", _T("Stage/Monster/Monster_1.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 11, 1, 0, 0, 10, 0, 1.5f);
		break;
	case 1:
		m_tInfo.fSpeed = 200.f;
		m_iHP = 2;

		m_fCoolDown = 1.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster2", _T("Stage/Monster/Monster_2.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 11, 1, 0, 0, 10, 0, 1.5f);
		break;
	case 2:
		m_tInfo.fSpeed = 350.f;
		m_iHP = 3;

		m_fCoolDown = 1.f;
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster3", _T("Stage/Monster/Monster_3.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 11, 1, 0, 0, 10, 0, 1.5f);
		break;
	case 3:
		m_tInfo.fSpeed = 550.f;
		m_iHP = 4;

		m_fCoolDown = 1.f;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Monster1", _T("Stage/Monster/Monster_1.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 11, 1, 0, 0, 10, 0, 1.5f);
		break;
	}

}

int CCommonMonster::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	SetDistance();
	SetBarrel(&m_Barrel, 0.f, 20.f);

	IsMoving();
	IsOutRange();
	IsFire();
	CMonster::IsDead();
	CGameObject::UpdateRect();
	

	return NO_EVENT;
}

void CCommonMonster::Render(HDC hDC)
{
	switch (m_Various)
	{
	case 0:
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	case 1:
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	case 2:
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	case 3:
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	}
}

void CCommonMonster::Release()
{
	m_pTexture->SafeDelete();
}

void CCommonMonster::IsMoving()
{
	switch (m_MoveType)
	{
	case 0:
		// �����̵�
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	case 1:
		// ������ �̵�
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		m_tInfo.fX += (m_tInfo.fSpeed * 0.3f) * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	case 2:
		// ������ �̵�
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		m_tInfo.fX -= (m_tInfo.fSpeed * 0.5f) * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	case 3:
		// �÷��̾ x������ �����ϸ� ����
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		if (m_tInfo.fX < m_pTarget->GetInfo().fX)
		{
			// �÷��̾��� ������ ����
			m_tInfo.fX += (m_tInfo.fSpeed * 0.5f) * DELTA_TIME;
		}
		else
		{
			// �÷��̾��� ������ ����
			m_tInfo.fX -= (m_tInfo.fSpeed * 0.5f) * DELTA_TIME;
		}
		break;
	}

}

void CCommonMonster::IsFire()
{
	if (m_fCoolDown >= 0)
		m_fCoolDown -= DELTA_TIME;

	switch (m_FireType)
	{
	case 0:
		// 2�� �ܹ߻��
		if (m_fCoolDown < 0)
		{
			CGameObject* pObject;
			pObject = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pObject)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pObject)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pObject);

			m_fCoolDown += 2.f;
		}
		break;
	case 1:
		// 0.2�� ���߻��(3����)
		if (m_fCoolDown < 0)
		{
			CGameObject* pObject;
			pObject = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pObject)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pObject)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pObject);

			m_fCoolDown += 0.2f;
			++m_iShotCount;
		}
		if (m_iShotCount >= 3)
		{
			m_fCoolDown += 3.0f;
			m_iShotCount = 0;
		}
		break;
	case 2:
		break;
	case 3:
		// �÷��̾�� �Ÿ��� ��������� ���߻��
		if (m_fDistance < 300.f)
		{

			if (m_fCoolDown < 0)
			{
				CGameObject* pObject;
				pObject = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
				m_fAngle = GetAngle(m_pTarget, &m_Barrel);
				dynamic_cast<CMonBullet*>(pObject)->SetInfo(SMALL, m_fAngle);
				dynamic_cast<CMonBullet*>(pObject)->Initialize();
				CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pObject);

				m_fCoolDown += 0.1f;
			}

		}
		break;
	case 4:
		// ��ź ����
		if (m_fCoolDown < 0)
		{
			CGameObject* pObject;
			pObject = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pObject)->SetInfo(BOMB, m_fAngle);
			dynamic_cast<CMonBullet*>(pObject)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pObject);

			m_fCoolDown += 3.f;
		}

		break;

	}


}

