#include "stdafx.h"
#include "Items.h"


CItems::CItems()
{
	Initialize();
}


CItems::~CItems()
{
}

void CItems::Initialize()
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_RandomAngle = 0.01745f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (6.28319f - 0.01745f)));
	cout << m_RandomAngle << endl;
	m_IsAvailable = true;
	m_tInfo.fSpeed = 150.f;
	m_TimeLimit = 0.0f;

	m_pAnimator = new CAnimator;

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Item_Power", _T("Stage/Item/Item_Power.bmp"));
	m_pTexture->SetColorKey(RGB(0, 128, 128));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 6, 1, 0, 0, 5, 0, 3.f);
}

int CItems::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;

	
	Move();
	IsOutofRange();


	CGameObject::UpdateRect();
	return NO_EVENT;
}

void CItems::Render(HDC hDC)
{
	//Rectangle(hDC, m_tInfo.fX - 20, m_tInfo.fY - 20, m_tInfo.fX + 20, m_tInfo.fY + 20);
	CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 3.f, 2.f);
	m_pAnimator->AnimateClip(0, hDC, m_tImgInfo);

	
}

void CItems::Move()
{
	if ( 20.f<=m_TimeLimit)
	{
		m_IsAvailable = false;
	}
	else
	{
		m_TimeLimit += DELTA_TIME;
	}
	m_tInfo.fX += cosf(m_RandomAngle)*m_tInfo.fSpeed*DELTA_TIME;
	m_tInfo.fY += sinf(m_RandomAngle)*m_tInfo.fSpeed*DELTA_TIME;

}

void CItems::IsOutofRange()
{
	CGameObject::UpdateRect();
	if (!m_IsAvailable)
	{
		if (0 >= m_tRect.left || 0 >= m_tRect.top
			|| WINCX <= m_tRect.right || WINCY <= m_tRect.bottom)
		{
			m_bIsDead = true;
			//Release();
		}
	}
	else
	{
		if (0 >= m_tRect.left || 0 >= m_tRect.top
			|| WINCX <= m_tRect.right || WINCY <= m_tRect.bottom)
		{
			m_tInfo.fSpeed *= -1;
			m_RandomAngle += 1.0472f;
			//m_bIsDead = true;
			//Release();
		}
	}
	

}

void CItems::Release()
{
	m_pTexture->SafeDelete();
}
