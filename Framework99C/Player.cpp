#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "WingMan.h"

CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	//Release();
}

void CPlayer::SetBulletLst(OBJLIST* pBulletLst)
{
}

void CPlayer::AddWingMan()
{
	CGameObject* pGameObj = new CWingMan;
	pGameObj->SetPos(m_WingManLoc[wingCount].x, m_WingManLoc[wingCount].y);
	dynamic_cast<CWingMan*>(pGameObj)->SetLocation(&m_WingManLoc[wingCount]);
	CObjectMgr::GetInstance()->AddObject(OBJECT_WINGMAN,pGameObj);
	m_WingMan[wingCount] = pGameObj;
	++wingCount;
}

void CPlayer::UpdateWingMan()
{
	m_WingManLoc[0].x = m_tInfo.fX - 50;
	m_WingManLoc[0].y = m_tInfo.fY + 50;

	m_WingManLoc[1].x = m_tInfo.fX + 50;
	m_WingManLoc[1].y = m_tInfo.fY + 50;

	m_WingManLoc[2].x = m_tInfo.fX - 100;
	m_WingManLoc[2].y = m_tInfo.fY + 70;

	m_WingManLoc[3].x = m_tInfo.fX + 100;
	m_WingManLoc[3].y = m_tInfo.fY + 70;
}

POINT * CPlayer::GetWingManPos()
{
	return m_WingManLoc;
}

void CPlayer::Initialize()
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 400.f;
	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tInfo.fSpeed = 350.f;



	//m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Player", _T("Stage/Player/Move_TB_A.bmp"));

	m_WingManLoc[0].x = m_tInfo.fX - 50;
	m_WingManLoc[0].y = m_tInfo.fY + 50;

	m_WingManLoc[1].x = m_tInfo.fX + 50;
	m_WingManLoc[1].y = m_tInfo.fY + 50;

	m_WingManLoc[2].x = m_tInfo.fX - 100;
	m_WingManLoc[2].y = m_tInfo.fY + 70;

	m_WingManLoc[3].x = m_tInfo.fX + 100;
	m_WingManLoc[3].y = m_tInfo.fY + 70;

	wingCount = 0;

	//m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Player", _T("Stage/Player/Player_left.bmp"));
	//m_pTexture->SetColorKey(RGB(255, 255, 255));


	// TEST ---------------------------------------------------

	m_pAnimator = new CAnimator;

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("player_default", _T("Stage/Player/Player.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 2, 1, 0, 0, 1, 0, 1.f);

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("player", _T("Stage/Player/Move_TB_A.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 7, 1, 0, 0, 6, 0, 1.f);

	// --------------------------------------------------------

}

int CPlayer::Update()
{
	KeyInput();
	CGameObject::UpdateRect();

	//CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY * 76.f/33.f);
	//m_pTexture->SetXY(0.f, 2.f);

	UpdateWingMan();
	//m_pTexture->SetXY(0.f, 2.f);


	return NO_EVENT;
}

void CPlayer::Render(HDC hDC)
{
	//m_pTexture->DrawTexture(hDC, m_tImgInfo);

	// TEST ---------------------------------------------------
	if(CKeyboardMgr::GetInstance()->KeyPressed(KEY_UP))
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 1.f, 76.f / 33.f);
		m_pAnimator->RunAnim(1, hDC, m_tImgInfo);
	}
	else
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 1.f, 1.f);
		m_pAnimator->RunAnim(0, hDC, m_tImgInfo);
	}
	// --------------------------------------------------------

	//디버그용
	/*Rectangle(hDC, m_WingManLoc[0].x - 10, m_WingManLoc[0].y - 10, m_WingManLoc[0].x + 10, m_WingManLoc[0].y + 10);
	Rectangle(hDC, m_WingManLoc[1].x - 10, m_WingManLoc[1].y - 10, m_WingManLoc[1].x + 10, m_WingManLoc[1].y + 10);
	Rectangle(hDC, m_WingManLoc[2].x - 10, m_WingManLoc[2].y - 10, m_WingManLoc[2].x + 10, m_WingManLoc[2].y + 10);
	Rectangle(hDC, m_WingManLoc[3].x - 10, m_WingManLoc[3].y - 10, m_WingManLoc[3].x + 10, m_WingManLoc[3].y + 10);*/

}

void CPlayer::Release()
{
	m_pTexture->SafeDelete();
}

CGameObject* CPlayer::CreateBullet()
{
	return CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
}

CGameObject* CPlayer::CreateBullet(BULLET_DIRECTION eDir)
{
	CGameObject* pBullet = CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
	dynamic_cast<CBullet*>(pBullet)->SetDirection(eDir);

	return pBullet;
}

void CPlayer::KeyInput()
{
	CKeyboardMgr::GetInstance()->Update();
	VECTOR2D vector(0, 0);
	//// 몬스터와 충돌하면 뒤로 밀어버림 - 정보성 -
	//if (CCollsionMgr::GetInstance()->CollisionRect(m_ObjLst[OBJECT_PLAYER], m_ObjLst[OBJECT_MONSTER],&vector))
	//{
	//	m_tInfo.fX += vector.x;
	//	m_tInfo.fY += vector.y;
	//}
	//else
	//{
	CObjectMgr* objMgr = CObjectMgr::GetInstance();
	CCollsionMgr::GetInstance()->CollisionRectEX(objMgr->GetObjectList(OBJECT_PLAYER), objMgr->GetObjectList(OBJECT_MONSTER));
		//플레이어 영역 제한 버벅거리는거 없음.
		if (m_tRect.left > 0)
		{
			if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				m_tInfo.fX -= m_tInfo.fSpeed  * DELTA_TIME;
			}
			
		}
		if (m_tRect.right < WINCX)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				m_tInfo.fX += m_tInfo.fSpeed  * DELTA_TIME;
			}
		}
		if (m_tRect.top > 0)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				m_tInfo.fY -= m_tInfo.fSpeed  * DELTA_TIME;
			}
			
		}
		if (m_tRect.bottom < WINCY)
		{
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
			}
			
		}
	static int nMaximumBullet = MAXIMUM_MISSILE;

	// BUTTON_A : 키보드를 누를 경우 최대 4개의 미사일까지 발사
	if (!m_bArrButton[BUTTON_A] && (GetAsyncKeyState('A') & 0x8000))
	{
		CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET,CreateBullet(BULLET_UP));
		if (!(--nMaximumBullet))
		{
			m_bArrButton[BUTTON_A] = true;
			nMaximumBullet = MAXIMUM_MISSILE;
		}
	}
	if (!GetAsyncKeyState('A'))
		m_bArrButton[BUTTON_A] = false;

		// BUTTON_S : 필살기 버튼 연속입력 방지
		if (!m_bArrButton[BUTTON_S] && (GetAsyncKeyState('S') & 0x8000))
		{
			CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP));
			for (int i = 0; i < wingCount; ++i)
			{
				dynamic_cast<CWingMan*>(m_WingMan[i])->Fire();
			}
			m_bArrButton[BUTTON_S] = true;
			m_bIsAttack = true;
		}
	if (!GetAsyncKeyState('S'))
		m_bArrButton[BUTTON_S] = false;
	//if (GetAsyncKeyState('W') & 0x8000)
	//	m_pBulletLst->push_back(CreateBullet(BULLET_UP));
	//if (GetAsyncKeyState('D') & 0x8000)
	//	m_pBulletLst->push_back(CreateBullet(BULLET_RIGHT));
}
