#include "stdafx.h"
#include "Boss.h"


CBoss::CBoss()
{
}


CBoss::~CBoss()
{
	Release();
}

void CBoss::Initialize()
{
	m_iShotCount = 0;
	m_fCoolDown = 3.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;
	m_tInfo.fSpeed = 0.f;	// ��ǻ� ����
	m_iHP = 1000;

	m_pAnimator = new CAnimator;
	switch (m_Various)
	{
	case 0:
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Boss", _T("Stage/Monster/LBossMain.bmp"));
		m_pTexture->SetColorKey(RGB(82, 90, 74));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 8, 2, 0, 0, 7, 0, 2.0f);	// 1ȸ�� ���

		break;
	}

}

int CBoss::Update()
{
	// ������ �����̺�Ʈ �ʿ����
	// ��� ����� �̹�����ȭ

	SetBarrel(&m_Barrel, 80.f, 30.f);
	SetBarrel(&m_Barrel2, -80.f, 30.f);
	SetBarrel(&m_Barrel3, 0.f, 40.f);
	SetBarrel(&m_Barrel4, 0.f, 40.f);

	IsMoving();
	IsFire();

	CGameObject::UpdateRect();
	CGameObject::UpdateImgInfo(300.f, 300.f);

	return NO_EVENT;

}

void CBoss::Render(HDC hDC)
{
	switch (m_Various)
	{
	case 0:
		CGameObject::UpdateImgInfo(m_tInfo.fCX * 1.f, m_tInfo.fCY * 1.f);
		m_pAnimator->SetImgInfo(0, m_tImgInfo);
		m_pAnimator->AnimateClip(0, hDC);

		break;
	}

}

void CBoss::Release()
{
	m_pTexture->SafeDelete();
}

void CBoss::IsMoving()
{
	switch (m_MonType)
	{
	case 0:
		break;
	}
}

void CBoss::IsFire()
{
	switch (m_FireType)
	{
	case 0:
		break;
	}
}
