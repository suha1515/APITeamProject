#include "stdafx.h"
#include "MidBoss.h"
#include "MonBullet.h"

CMidBoss::CMidBoss()
	:m_fAngle2(0.f), m_fCoolDown2(0.f)
{
}


CMidBoss::~CMidBoss()
{
	Release();
}

void CMidBoss::Initialize()
{
	m_iShotCount = 0;
	m_fCoolDown = 1.f;

	m_pAnimator = new CAnimator;

	
	switch (m_Various)
	{
	case 0:
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 150.f;
		m_iHP = 40;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MidBoss1", _T("Stage/Monster/Monster_4.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 2, 1, 1, 0, 1, 0, 1.0f);
		break;
	case 1:
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 100.f;
		m_iHP = 100;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MidBoss2", _T("Stage/Monster/MidAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 2, 1, 0, 0, 1, 0, 1.0f);
		break;
	case 2:
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 50.f;
		m_iHP = 150;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MidBoss3", _T("Stage/Monster/BigAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 1, 1, 0, 0, 0, 0, 1.0f);
		break;

	case 3:
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 100.f;
		m_tInfo.fSpeed = 50.f;
		m_iHP = 300;

		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("MidBoss3", _T("Stage/Monster/BigAirPlan.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 1, 1, 0, 0, 0, 0, 1.0f);
		break;

	}



	m_DeadEffect = false;
	m_DeadTime = 0.0f;

}

int CMidBoss::Update()
{
	if (m_bIsDead)
	{
		
		return DEAD_OBJ;

	}


	switch (m_Various)
	{
	case 0:
		SetBarrel(&m_Barrel, 80.f, 30.f);
		SetBarrel(&m_Barrel2, -80.f, 30.f);
		SetBarrel(&m_Barrel3, 0.f, 40.f);

		break;
	case 1:
		SetBarrel(&m_Barrel, 85.f, -10.f);
		SetBarrel(&m_Barrel2, -85.f, -10.f);
		SetBarrel(&m_Barrel3, 0.f, 100.f);

		break;
	case 2:
		SetBarrel(&m_Barrel, 100.f, 10.f);
		SetBarrel(&m_Barrel2, -100.f, 10.f);
		SetBarrel(&m_Barrel3, 0.f, 110.f);

		break;
	case 3:
		SetBarrel(&m_Barrel, 100.f, 10.f);
		SetBarrel(&m_Barrel2, -100.f, 10.f);
		SetBarrel(&m_Barrel3, 0.f, 110.f);

		break;
	}

	if (nullptr == m_pTarget)
	{
		m_pTarget = CObjectMgr::GetInstance()->GetPlayer();
		m_fAngle = GetAngle(m_pTarget, &m_Barrel) - 20.f;
		m_fAngle2 = GetAngle(m_pTarget, &m_Barrel) + 20.f;

	}
	if (!m_DeadEffect)
	{
		IsMoving();
		IsOutRange();
		IsFire();
		IsDead();
	}
	else
	{
		DeadEffect();
	}
	
	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(300.f, 300.f);

	return NO_EVENT;
}

void CMidBoss::Render(HDC hDC)
{
	switch (m_Various)
	{
	case 0:
		CGameObject::UpdateImgInfo(m_tInfo.fCX * 2.5f, m_tInfo.fCY * 2.f);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	case 1:
		CGameObject::UpdateImgInfo(m_tInfo.fCX * 2.5f, m_tInfo.fCY * 2.5f);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	case 2:
		CGameObject::UpdateImgInfo(m_tInfo.fCX * 3.f, m_tInfo.fCY * 3.f);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	case 3:
		CGameObject::UpdateImgInfo(m_tInfo.fCX * 3.f, m_tInfo.fCY * 3.f);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);
		break;
	}
}

void CMidBoss::Release()
{
	m_pTexture->SafeDelete();
}

void CMidBoss::IsMoving()
{
	m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

	switch (m_MoveType)
	{
	case 0:
		// 하향이동
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	case 1:
		// 하향이동 하다 제자리에서 플레이어 추적
		if (m_tInfo.fY < 200.f)
		{
			m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		}
		else
		{
			if (m_tInfo.fX < m_pTarget->GetInfo().fX)
			{
				// 플레이어의 좌측에 있음
				m_tInfo.fX += (m_tInfo.fSpeed * 0.5f) * DELTA_TIME;
			}
			else
			{
				// 플레이어의 우측에 있음
				m_tInfo.fX -= (m_tInfo.fSpeed * 0.5f) * DELTA_TIME;
			}
		}
		CGameObject::UpdateRect();
		break;
	case 2:
		// 하향이동
		m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		CGameObject::UpdateRect();
		break;
	}

}

void CMidBoss::DeadEffect()
{
	if (m_DeadTime > 3.5f)
	{
		m_bIsDead = true;
		DropItem();
		//마지막 죽었을때 
		CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, IMGINFO(m_tInfo.fX , m_tInfo.fY , 0.5, 0.5, 300,300, 1, 1));
	}
	else
	{
		list<PARTICLE_INFO>::iterator iter_begin = m_EffectINFO.begin();
		list<PARTICLE_INFO>::iterator iter_end = m_EffectINFO.end();
		for (;iter_begin!=iter_end;)
		{
			// m_DeadTIme 보다 리스트에 들어간 시간이 커질경우 이펙트 실행
			if (m_DeadTime >= iter_begin->effect_Time)
			{
				//이펙트 출력부분
				CEffectMgr::GetInstance()->AddEffect(EXPLOSIVE_1, iter_begin->effect_Info);
				iter_begin = m_EffectINFO.erase(iter_begin);
			}
			else
				iter_begin++;
		}
		m_tInfo.fCX -= DELTA_TIME*15.0f;
		m_tInfo.fCY -= DELTA_TIME*15.0f;
		m_DeadTime += DELTA_TIME;
	}
}

void CMidBoss::IsFire()
{
	if (m_fCoolDown >= 0)
		m_fCoolDown -= DELTA_TIME;
	if (m_fCoolDown2 >= 0)
		m_fCoolDown2 -= DELTA_TIME;


	switch (m_FireType)
	{
	case 0:
		// 쌍발 6연사
		if (m_fCoolDown < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

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
			dynamic_cast<CMonBullet*>(pBullet1)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			m_fCoolDown += 0.1f;
			++m_iShotCount;
		}
		if (m_iShotCount > 5)
		{
			m_fCoolDown += 3.0f;
			m_iShotCount = 0;
		}
		break;
	case 1:
		// 3갈래 공격 * 2
		if (m_fCoolDown < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

			// 1번포신
			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pBullet1)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet1)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) + 10.f;
			dynamic_cast<CMonBullet*>(pBullet2)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet2)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			CGameObject* pBullet3;
			pBullet3 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) - 10.f;
			dynamic_cast<CMonBullet*>(pBullet3)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet3)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet3);

			// 2번포신
			CGameObject* pBullet4;
			pBullet4 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel2);
			dynamic_cast<CMonBullet*>(pBullet4)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet4)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet4);

			CGameObject* pBullet5;
			pBullet5 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel2) + 10.f;
			dynamic_cast<CMonBullet*>(pBullet5)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet5)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet5);

			CGameObject* pBullet6;
			pBullet6 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel2) - 10.f;
			dynamic_cast<CMonBullet*>(pBullet6)->SetInfo(SMALL, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet6)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet6);

			m_fCoolDown += 0.1f;
			++m_iShotCount;
		}
		if (m_iShotCount > 2)
		{
			m_fCoolDown += 3.0f;
			m_iShotCount = 0;
		}
		break;
	case 2:
		// 회전난사
		if (m_fCoolDown < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

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

			m_fCoolDown += 0.05f;
			++m_iShotCount;
		}
		if (m_iShotCount > 10)
		{
			m_fCoolDown += 2.0f;
			m_iShotCount = 0;
			m_fAngle = GetAngle(m_pTarget, &m_Barrel) - 10.f;
			m_fAngle2 = GetAngle(m_pTarget, &m_Barrel) + 10.f;
		}
		break;
	case 3:
		// 고속탄과 저속탄 섞어사격
		if (m_fCoolDown < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

			// 고속사격
			CGameObject* pBullet1;
			pBullet1 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel.x, m_Barrel.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel);
			dynamic_cast<CMonBullet*>(pBullet1)->SetInfo(FAST, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet1)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet1);

			CGameObject* pBullet2;
			pBullet2 = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel2.x, m_Barrel2.y);
			m_fAngle = GetAngle(m_pTarget, &m_Barrel2);
			dynamic_cast<CMonBullet*>(pBullet2)->SetInfo(FAST, m_fAngle);
			dynamic_cast<CMonBullet*>(pBullet2)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet2);

			m_fCoolDown += 1.5f;
		}
		// 저속난사
		if (m_fCoolDown2 < 0)
		{
			m_pTarget = CObjectMgr::GetInstance()->GetPlayer();

			CGameObject* pBullet;
			pBullet = CAbstractFactory<CMonBullet>::CreateObject(m_Barrel3.x, m_Barrel3.y);
			m_fAngle2 = GetAngle(m_pTarget, &m_Barrel3) + (float(rand() % 30) - 15.f);
			dynamic_cast<CMonBullet*>(pBullet)->SetInfo(SMALL, m_fAngle2);
			dynamic_cast<CMonBullet*>(pBullet)->Initialize();
			CObjectMgr::GetInstance()->AddObject(OBJECT_MONBULLET, pBullet);

			m_fCoolDown2 += 0.05f;
			++m_iShotCount;

			if (m_iShotCount > 10)
			{
				m_fCoolDown2 += 2.0f;
				m_iShotCount = 0;
			}


		}
		break;
	}

}
//업데이트에서 계속 체크
void CMidBoss::IsDead()
{
	if (m_iHP <= 0)
	{
		m_DeadEffect = true;

		//죽음 이펙트 설정부분

		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX - 70, m_tInfo.fY + 40, 0.5, 0.5, 100, 100, 1, 1), 0.5f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX + 40, m_tInfo.fY - 60, 0.5, 0.5, 120, 120, 1, 1), 1.2f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX + 100, m_tInfo.fY + 70, 0.5, 0.5,100, 100, 1, 1), 1.7f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX - 90, m_tInfo.fY - 10, 0.5, 0.5, 150, 150, 1, 1), 2.4f));
		m_EffectINFO.push_back(PARTICLE_INFO(IMGINFO(m_tInfo.fX - 10, m_tInfo.fY + 50, 0.5, 0.5, 200, 200, 1, 1), 3.2f));

		////////////////////////

	}
}
