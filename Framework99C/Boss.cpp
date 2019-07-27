#include "stdafx.h"
#include "Boss.h"
#include "MonBullet.h"


CBoss::CBoss()
	:m_TransPhase(0), m_BossHeadInfo(0, 0, 0, 0, 60, 60, 0.9f, 1.2f), m_BossLegInfo1(0, 0, 0, 0, 200, 200, 1.f, 1.f), m_BossLegInfo2(0, 0, 0, 0, 200, 200, 1.f, 1.f),
	m_BossLegInfo3(0, 0, 0, 0, 200, 200, 1.f, 1.f), m_BossLegInfo4(0, 0, 0, 0, 200, 200, 1.f, 1.f), m_transTime(2.f), m_fCoolDown2(5.f), m_fCoolDown3(7.f), m_fCoolDown4(5.f),
	m_iShotCount2(0), m_iShotCount3(0), m_DeadTime(0.f), m_LegBreak1(false), m_LegBreak2(false), m_LegBreak3(false), m_LegBreak4(false), m_HeadBreak(false), m_DeadEffect(false)
{
}


CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{
	m_iShotCount = 0;
	m_fCoolDown = 5.f;

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 300.f;
	m_tInfo.fSpeed = 150.f;	// �ʱ� ���ټӵ�
	m_iHP = 1500;

	m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

	// ���� ����
	m_pAnimator = new CAnimator;
	// ���� ����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossBody", _T("Stage/Monster/LBossMain.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 8, 2, 0, 0, 0, 0, 2.0f);	// ������ ���� ���·� ����
	// ���� ��ġ����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossBody1", _T("Stage/Monster/LBossMain.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 8, 2, 0, 0, 7, 0, 2.0f);	// 1ȸ�� ���
	// ���� �ı�
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossBody2", _T("Stage/Monster/LBossMain.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 8, 2, 0, 1, 0, 1, 2.0f);	// 1ȸ�� ���

	// ���� �Ӹ�
	m_pAnimatorHead = new CAnimator;
	// �Ӹ� ����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossHead", _T("Stage/Monster/LBossCenter.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorHead->AddAnimInfo(m_pTexture, AT_RETAIN, 7, 3, 0, 1, 0, 1, 2.0f);	// ������ ���� ���·� ����
	// �Ӹ�����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossHead1", _T("Stage/Monster/LBossCenter.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorHead->AddAnimInfo(m_pTexture, AT_RETAIN, 7, 3, 0, 1, 6, 1, 2.0f);	// ��������
	// �Ӹ�����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossHead2", _T("Stage/Monster/LBossCenter.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorHead->AddAnimInfo(m_pTexture, AT_RETAIN, 7, 3, 0, 0, 0, 0, 2.0f);
	
	// �����ٸ�1(���ϴ�)
	m_pAnimatorLeg1 = new CAnimator;
	// �ٸ� ����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg1", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg1->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 0, 0, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg1-1", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg1->AddAnimInfo(m_pTexture, AT_ONCE_DESTROY, 9, 3, 0, 0, 8, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�ȸ��
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg1-2", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg1->AddAnimInfo(m_pTexture, AT_LOOP, 9, 3, 0, 1, 3, 1, 0.15f);	// �ٸ� ȸ��
	//�ٸ��ı�
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg1-3", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg1->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 2, 0, 2, 2.0f);

	// �»��
	m_pAnimatorLeg2 = new CAnimator;
	// �ٸ� ����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg2", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg2->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 0, 0, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg2-1", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg2->AddAnimInfo(m_pTexture, AT_ONCE_DESTROY, 9, 3, 0, 0, 8, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�ȸ��
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg2-2", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg2->AddAnimInfo(m_pTexture, AT_LOOP, 9, 3, 0, 1, 3, 1, 0.15f);		// �ٸ� ȸ��
	//�ٸ��ı�
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg2-3", _T("Stage/Monster/LBossLeft.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg2->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 2, 0, 2, 2.0f);


	// ���ϴ�
	m_pAnimatorLeg3 = new CAnimator;
	// �ٸ� ����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg3", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg3->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 0, 0, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg3-1", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg3->AddAnimInfo(m_pTexture, AT_ONCE_DESTROY, 9, 3, 0, 0, 8, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�ȸ��
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg3-2", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg3->AddAnimInfo(m_pTexture, AT_LOOP, 9, 3, 0, 1, 3, 1, 0.15f);	// �ٸ� ȸ��
	//�ٸ��ı�
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg3-3", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg3->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 2, 0, 2, 2.0f);


	// ����
	m_pAnimatorLeg4 = new CAnimator;
	// �ٸ� ����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg4", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg4->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 0, 0, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�����
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg4-1", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg4->AddAnimInfo(m_pTexture, AT_ONCE_DESTROY, 9, 3, 0, 0, 8, 0, 2.0f);	// �ٸ��� ���� ���·� ����
	//�ٸ�ȸ��
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg4-2", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg4->AddAnimInfo(m_pTexture, AT_LOOP, 9, 3, 0, 1, 3, 1, 0.15f);	// �ٸ� ȸ��
	//�ٸ��ı�
	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("BossLeg4-3", _T("Stage/Monster/LBossRight.bmp"));
	m_pTexture->SetColorKey(RGB(82, 90, 74));
	m_pAnimatorLeg4->AddAnimInfo(m_pTexture, AT_RETAIN, 9, 3, 0, 2, 0, 2, 2.0f);


}

int CBoss::Update()
{
	m_transTime -= DELTA_TIME;

	m_BossHeadInfo.fX = m_tInfo.fX - 38.f;
	m_BossHeadInfo.fY = m_tInfo.fY - 68.f;

	m_BossLegInfo1.fX = m_tInfo.fX - 300.f;
	m_BossLegInfo1.fY = m_tInfo.fY + 0.f;

	m_BossLegInfo2.fX = m_tInfo.fX - 300.f;
	m_BossLegInfo2.fY = m_tInfo.fY - 200.f;

	m_BossLegInfo3.fX = m_tInfo.fX + 90.f;
	m_BossLegInfo3.fY = m_tInfo.fY + 0.f;

	m_BossLegInfo4.fX = m_tInfo.fX + 90.f;
	m_BossLegInfo4.fY = m_tInfo.fY - 200.f;


	SetBarrel(&m_Barrel, -75.f, -40.f);	// �����ѱ�
	SetBarrel(&m_Barrel2, 55.f, -40.f);	// �����ѱ�
	SetBarrel(&m_Barrel3, -5.f, -40.f);	// �Ӹ�
	SetBarrel(&m_Barrel4, -7.f, 30.f);	// ��(����ź)

	if (!m_DeadEffect)
	{
		IsDead();
		PhaseShift();
		IsMoving();
		IsFire();
		DeadPartsCheck();
		PrintEffect();

	}
	else
	{
		DeadEffect();
	}



	//CMonster::IsDead();
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(300.f, 300.f);

	return NO_EVENT;

}

void CBoss::Render(HDC hDC)
{

	CGameObject::UpdateImgInfo(m_tInfo.fCX * 1.f, m_tInfo.fCY * 1.f);
	m_pAnimator->SetImgInfo(0, m_tImgInfo);
	m_pAnimator->AnimateClip(0, hDC);

	m_pAnimatorHead->SetImgInfo(0, m_BossHeadInfo);
	m_pAnimatorHead->AnimateClip(0, hDC);

	m_pAnimatorLeg1->SetImgInfo(1, m_BossLegInfo1);
	m_pAnimatorLeg1->AnimateClip(1, hDC);

	m_pAnimatorLeg2->SetImgInfo(1, m_BossLegInfo2);
	m_pAnimatorLeg2->AnimateClip(1, hDC);

	m_pAnimatorLeg3->SetImgInfo(1, m_BossLegInfo3);
	m_pAnimatorLeg3->AnimateClip(1, hDC);

	m_pAnimatorLeg4->SetImgInfo(1, m_BossLegInfo4);
	m_pAnimatorLeg4->AnimateClip(1, hDC);

	if (m_transTime <= 0)
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX * 1.f, m_tInfo.fCY * 1.f);
		m_pAnimator->SetImgInfo(1, m_tImgInfo);
		m_pAnimator->AnimateClip(1, hDC);

		m_pAnimatorHead->SetImgInfo(1, m_BossHeadInfo);
		m_pAnimatorHead->AnimateClip(1, hDC);

		if (m_TransPhase <= 0)
		{
			m_pAnimatorLeg1->SetImgInfo(2, m_BossLegInfo1);
			m_pAnimatorLeg1->AnimateClip(2, hDC);

		}
		if (m_TransPhase <= 1)
		{
			m_pAnimatorLeg3->SetImgInfo(2, m_BossLegInfo3);
			m_pAnimatorLeg3->AnimateClip(2, hDC);
		}
		if (m_TransPhase <= 2)
		{
			m_pAnimatorLeg2->SetImgInfo(2, m_BossLegInfo2);
			m_pAnimatorLeg2->AnimateClip(2, hDC);

		}
		if (m_TransPhase <= 3)
		{
			m_pAnimatorLeg4->SetImgInfo(2, m_BossLegInfo4);
			m_pAnimatorLeg4->AnimateClip(2, hDC);

		}
		

	}

	// ü�º��� �����ı�
	if (m_TransPhase >= 1)
	{
		// �ٸ�(���ϴ�) �ı�
		m_pAnimatorLeg1->SetImgInfo(3, m_BossLegInfo1);
		m_pAnimatorLeg1->AnimateClip(3, hDC);
	}
	if (m_TransPhase >= 2)
	{
		// �ٸ�(���ϴ�) �ı�
		m_pAnimatorLeg3->SetImgInfo(3, m_BossLegInfo3);
		m_pAnimatorLeg3->AnimateClip(3, hDC);
	}
	if (m_TransPhase >= 3)
	{
		// �ٸ�(�»��) �ı�
		m_pAnimatorLeg2->SetImgInfo(3, m_BossLegInfo2);
		m_pAnimatorLeg2->AnimateClip(3, hDC);
	}
	if (m_TransPhase >= 4)
	{
		// �ٸ�(����) �ı�
		m_pAnimatorLeg4->SetImgInfo(3, m_BossLegInfo4);
		m_pAnimatorLeg4->AnimateClip(3, hDC);
	}
	if (m_TransPhase >= 5)
	{
		// �Ӹ� �ı�
		m_pAnimatorHead->SetImgInfo(2, m_BossHeadInfo);
		m_pAnimatorHead->AnimateClip(2, hDC);
	}

	if (m_bIsDead)
	{
		// �����ı�
		CGameObject::UpdateImgInfo(m_tInfo.fCX * 1.f, m_tInfo.fCY * 1.f);
		m_pAnimator->SetImgInfo(2, m_tImgInfo);
		m_pAnimator->AnimateClip(2, hDC);

	}

}

void CBoss::Release()
{
	m_pTexture->SafeDelete();
}

void CBoss::IsMoving()
{
	if (m_tInfo.fY < 300.f)
	{
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
	}
	CGameObject::UpdateRect();
}

void CBoss::IsFire()
{
	if (m_fCoolDown >= 0)
		m_fCoolDown -= DELTA_TIME;
	if (m_fCoolDown2 >= 0)
		m_fCoolDown2 -= DELTA_TIME;
	if (m_fCoolDown3 >= 0)
		m_fCoolDown3 -= DELTA_TIME;
	if (m_fCoolDown4 >= 0)
		m_fCoolDown4 -= DELTA_TIME;

	// ü�º��� ���Ϻ�ȭ
	// ���ź��� �ٷ�� �� ������.

	// 1,2������
	if (m_TransPhase <= 1)	// �մٸ� �ı� ��
	{
		// ����
		if (m_fCoolDown < 0)
		{
			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pBullet1)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet1)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel2);
			dynamic_cast<CMonBullet*>(pBullet2)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet2)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			m_fCoolDown += 0.1f;
			++m_iShotCount;
		}
		if (m_iShotCount > 9)
		{
			m_fCoolDown += 2.0f;
			m_iShotCount = 0;
		}

	}
	else if (m_TransPhase > 1 && m_TransPhase <= 3)	// �ٸ� ���� �ı� ������
	{
		// 1,2���� ����
		if (m_fCoolDown < 0)
		{
			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) + float(rand() % 30) - 15.f;
			dynamic_cast<CMonBullet*>(pBullet1)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet1)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);


			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_fAngle2 = GetAngle(m_pTarget, &m_Barrel2) + float(rand() % 30) - 15.f;
			dynamic_cast<CMonBullet*>(pBullet2)->SetInfo(SMALL, m_fAngle2);
			dynamic_cast<CMonBullet*>(pBullet2)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			m_fCoolDown += 0.05f;
			++m_iShotCount;

		}
		if (m_iShotCount > 19)
		{
			m_fCoolDown += 2.0f;
			m_iShotCount = 0;
		}

	}
	else if (m_TransPhase > 3 && m_TransPhase <= 5)	// ����� ������
	{
		// 1,2���� ��𵹸���
		if (m_fCoolDown < 0)
		{
			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			dynamic_cast<CMonBullet*>(pBullet1)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet1)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);
			m_fAngle += 5.f;

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			dynamic_cast<CMonBullet*>(pBullet2)->SetInfo(SMALL, m_fAngle2);
			dynamic_cast<CMonBullet*>(pBullet2)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);
			m_fAngle2 -= 5.f;

			m_fCoolDown += 0.1f;
			++m_iShotCount;

			if (m_iShotCount > 10)
			{
				m_fCoolDown += 1.0f;
				m_iShotCount = 0;
				m_fAngle = GetAngle(m_pTarget, &m_Barrel);
				m_fAngle2 = GetAngle(m_pTarget, &m_Barrel2);
			}


		}

	}

	// �Ӹ�����
	if (m_TransPhase <= 3)	// �ٸ� �ı� ������
	{
		// ������ 3����
		if (m_fCoolDown2 < 0)
		{
			CGameObject* pBullet3;
			pBullet3 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel3.x, m_Barrel3.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel3) + float(rand() % 10) - 5.f;
			dynamic_cast<CMonBullet*>(pBullet3)->SetInfo(FAST, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet3)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet3);
			m_fCoolDown2 += 0.05f;
			++m_iShotCount2;
		}
		if (m_iShotCount2 > 2)
		{
			m_fCoolDown2 += 1.0f;
			m_iShotCount2 = 0;
		}

	}
	else if (m_TransPhase > 3 && m_TransPhase <= 4)
	{
		// ������ 6����
		if (m_fCoolDown2 < 0)
		{
			CGameObject* pBullet3;
			pBullet3 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel3.x, m_Barrel3.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel3) + float(rand() % 20) - 10.f;
			dynamic_cast<CMonBullet*>(pBullet3)->SetInfo(FAST, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet3)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet3);
			m_fCoolDown2 += 0.05f;
			++m_iShotCount2;
		}
		if (m_iShotCount2 > 5)
		{
			m_fCoolDown2 += 1.0f;
			m_iShotCount2 = 0;
		}

	}

	// ����
	if (m_TransPhase > 3 && m_TransPhase <= 5)
	{
		if (m_fCoolDown3 < 0)
		{
			CGameObject* pBullet3;
			pBullet3 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel4.x, m_Barrel4.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel3) + float(rand() % 10) - 5.f;
			dynamic_cast<CMonBullet*>(pBullet3)->SetInfo(SLOW, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet3)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet3);
			m_fCoolDown3 += 0.5f;
			++m_iShotCount3;
		}
		if (m_iShotCount3 > 2)
		{
			m_fCoolDown3 += 5.0f;
			m_iShotCount3 = 0;
		}

	}

}

void CBoss::PhaseShift()
{
	// ������ ü�»��¸��� ����� ��ȭ��ų ����.
	// ������ -> �ٸ� �ϳ����ı�(4ȸ), �Ӹ�1ȸ, (�� 6�ܰ�)
	if (m_iHP > 1300)
	{
		// ������
		m_TransPhase = 0;
	}
	else if (m_iHP <= 1300 && m_iHP > 1100)
	{
		// �ٸ� 3����
		m_TransPhase = 1;

	}
	else if (m_iHP <= 1100 && m_iHP > 900)
	{
		// �ٸ� 2����
		m_TransPhase = 2;

	}
	else if (m_iHP <= 900 && m_iHP > 700)
	{
		// �ٸ� 1����
		m_TransPhase = 3;

	}
	else if (m_iHP <= 700 && m_iHP > 400)
	{
		// �ٸ� ����
		m_TransPhase = 4;

	}
	else if (m_iHP <= 400 && m_iHP > 0)
	{
		// �Ӹ� ����(��ü�� ����)
		m_TransPhase = 5;

	}
	else if(m_iHP <= 0)
	{
		// �ı�
		m_TransPhase = 6;
	}




}

void CBoss::DeadPartsCheck()
{
	if (m_iHP > 1300)
	{
		// ������
	}
	else if (m_iHP <= 1300 && m_iHP > 1100)
	{
		// �ٸ� 3����
		m_LegBreak1 = true;

	}
	else if (m_iHP <= 1100 && m_iHP > 900)
	{
		// �ٸ� 2����
		m_LegBreak2 = true;

	}
	else if (m_iHP <= 900 && m_iHP > 700)
	{
		// �ٸ� 1����
		m_LegBreak3 = true;

	}
	else if (m_iHP <= 700 && m_iHP > 400)
	{
		// �ٸ� ����
		m_LegBreak4 = true;

	}
	else if (m_iHP <= 400 && m_iHP > 0)
	{
		// �Ӹ� ����(��ü�� ����)
		m_HeadBreak = true;
	}
	else if (m_iHP <= 0)
	{
		// �ı�
		m_bIsDead = true;
	}

}

void CBoss::PrintEffect()
{

	// ���� ���Ǹ��� ����Ʈ ����ϵ���
	if(m_LegBreak1 && m_DeadTime == 0.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX - 160.f, m_tInfo.fY + 100.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}
	
	if (m_LegBreak2 && m_DeadTime == 1.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX + 160.f, m_tInfo.fY + 100.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}

	if (m_LegBreak3 && m_DeadTime == 2.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX - 160.f, m_tInfo.fY - 100.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}

	if (m_LegBreak4 && m_DeadTime == 3.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX + 160.f, m_tInfo.fY - 100.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}

	if (m_HeadBreak && m_DeadTime == 4.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX, m_tInfo.fY - 10.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}

	if (m_bIsDead && m_DeadTime == 5.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX, m_tInfo.fY - 10.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}
	if (m_bIsDead && m_DeadTime == 6.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX + 50.f, m_tInfo.fY - 100.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}
	if (m_bIsDead && m_DeadTime == 7.f)
	{
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX - 50.f, m_tInfo.fY + 100.f, 0.5, 0.5, 300, 300, 1, 1));
		m_DeadTime += 1.f;
	}


}

void CBoss::IsDead()
{
	if (m_iHP <= 0)
	{
		m_DeadEffect = true;

		//���� ����Ʈ �����κ�

		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX - 70, m_tInfo.fY + 40, 0.5, 0.5, 100, 100, 1, 1), 0.5f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX + 40, m_tInfo.fY - 60, 0.5, 0.5, 120, 120, 1, 1), 1.2f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX + 100, m_tInfo.fY + 70, 0.5, 0.5, 100, 100, 1, 1), 1.7f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX - 90, m_tInfo.fY - 10, 0.5, 0.5, 150, 150, 1, 1), 2.4f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX - 10, m_tInfo.fY + 50, 0.5, 0.5, 200, 200, 1, 1), 3.2f));
	}

}

void CBoss::DeadEffect()
{
	if (m_DeadTime > 3.5f)
	{
		//������ �׾����� 
		//CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX, m_tInfo.fY, 0.5, 0.5, 300, 300, 1, 1));
	}
	else
	{
		list<PARTICLE_INFO>::iterator iter_begin = m_EffectINFO.begin();
		list<PARTICLE_INFO>::iterator iter_end = m_EffectINFO.end();
		for (; iter_begin != iter_end;)
		{
			// m_DeadTIme ���� ����Ʈ�� �� �ð��� Ŀ����� ����Ʈ ����
			if (m_DeadTime >= iter_begin->effect_Time)
			{
				//����Ʈ ��ºκ�
				CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, iter_begin->effect_Info);
				iter_begin = m_EffectINFO.erase(iter_begin);
			}
			else
				iter_begin++;
		}
		m_DeadTime += DELTA_TIME;
	}

}
