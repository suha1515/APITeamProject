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
	m_tInfo.fCX = 54.f;
	m_tInfo.fCY = 32.f;
	m_RandomAngle = 0.01745f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (6.28319f - 0.01745f)));

	m_IsAvailable = true;
	m_tInfo.fSpeed = 150.f;
	m_TimeLimit = 0.0f;

	m_pAnimator = new CAnimator;
	if (m_Type == ITEM_TYPE::POWER)
	{
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Item_Power", _T("Stage/Item/Item_Power.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 6, 1, 0, 0, 5, 0, 3.f);
	}
	else if (m_Type == ITEM_TYPE::SPECIAL)
	{
		m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Item_Bomb", _T("Stage/Item/Item_Bomb.bmp"));
		m_pTexture->SetColorKey(RGB(0, 128, 128));
		m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 4, 1, 0, 0, 3, 0, 3.f);
	}
	
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
	//Rectangle(hDC, m_tInfo.fX - 27, m_tInfo.fY - 16, m_tInfo.fX + 27, m_tInfo.fY + 16);
	CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY);
	m_pAnimator->SetImgInfo(0, m_tImgInfo);
	m_pAnimator->AnimateClip(0, hDC);

	
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
		if (0 >= m_tRect.right || 0 >= m_tRect.bottom
			|| WINCX <= m_tRect.left || WINCY <= m_tRect.top)
		{
			m_bIsDead = true;
			//Release();
		}
	}
	else
	{
		static RECT tScreen = { 0 , 0, WINCX, WINCY };
		static RECT tOverlapped = {};

		IntersectRect(&tOverlapped, &tScreen, &m_tRect);

		if (tOverlapped.right - tOverlapped.left < m_tRect.right - m_tRect.left)
		{
			if(0 > m_tRect.left)
				m_tInfo.fX += 0 - m_tRect.left;
			else if (WINCX < m_tRect.right)
				m_tInfo.fX -= m_tRect.right - WINCX;

			m_tInfo.fSpeed *= -1;
			m_RandomAngle += 1.0472f;
		}

		if (tOverlapped.bottom - tOverlapped.top < m_tRect.bottom - m_tRect.top)
		{
			if (0 > m_tRect.top)
				m_tInfo.fY += 0 - m_tRect.top;
			else if (WINCY < m_tRect.bottom)
				m_tInfo.fY -= m_tRect.bottom - WINCY;

			m_tInfo.fSpeed *= -1;
			m_RandomAngle += 1.0472f;
		}
	}
	
}

void CItems::SetType(ITEM_TYPE type)
{
	m_Type = type;
}

ITEM_TYPE CItems::GetType()
{
	return m_Type;
}

void CItems::Release()
{
	m_pTexture->SafeDelete();
}
