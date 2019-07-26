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
	//차지샷 스킬 활성화시
	if (m_chargeWIngman)
	{
		//활성화후 사용중아니면 플레이어를 따라다니고
		// 사용하게 되면 조건문을 빠져나가 해당 위치를 고수하게 된다.
		if (!m_chargeShot)
		{
			m_WingManLoc[0].x = m_tInfo.fX - 60;
			m_WingManLoc[0].y = m_tInfo.fY - 100;

			m_WingManLoc[1].x = m_tInfo.fX + 60;
			m_WingManLoc[1].y = m_tInfo.fY - 100;

			m_WingManLoc[2].x = m_tInfo.fX - 120;
			m_WingManLoc[2].y = m_tInfo.fY - 120;

			m_WingManLoc[3].x = m_tInfo.fX + 120;
			m_WingManLoc[3].y = m_tInfo.fY - 120;
		}
	}
	else
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
}

void CPlayer::UpdateBarrel()
{
	//가운에 총구
	m_Barrel[0].x = m_tInfo.fX;
	m_Barrel[0].y = m_tInfo.fY - 50;

	//좌측 총구
	m_Barrel[1].x = m_tInfo.fX - 20;
	m_Barrel[1].y = m_tInfo.fY - 30;

	//우측 총구
	m_Barrel[2].x = m_tInfo.fX + 20;
	m_Barrel[2].y = m_tInfo.fY - 30;

	//끝좌측 총구
	m_Barrel[3].x = m_tInfo.fX - 50;
	m_Barrel[3].y = m_tInfo.fY - 20;

	//끝우측 총구
	m_Barrel[4].x = m_tInfo.fX + 50;
	m_Barrel[4].y = m_tInfo.fY - 20;
}

POINT * CPlayer::GetWingManPos()
{
	return m_WingManLoc;
}

void CPlayer::LevelUp()
{
	if (m_PowerLevel < 5)
	{
		AddWingMan();
		m_PowerLevel++;
	}	
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

	//가운에 총구
	m_Barrel[0].x = m_tInfo.fX;
	m_Barrel[0].y = m_tInfo.fY -50;

	//좌측 총구
	m_Barrel[1].x = m_tInfo.fX -20;
	m_Barrel[1].y = m_tInfo.fY -30;

	//우측 총구
	m_Barrel[2].x = m_tInfo.fX +20;
	m_Barrel[2].y = m_tInfo.fY -30;

	//끝좌측 총구
	m_Barrel[3].x = m_tInfo.fX - 50;
	m_Barrel[3].y = m_tInfo.fY - 20;

	//끝우측 총구
	m_Barrel[4].x = m_tInfo.fX +50;
	m_Barrel[4].y = m_tInfo.fY - 20;


	m_PowerLevel = 1;

	wingCount = 0;
	fFireRate = 0.f;
	fWingFireRate = 0.0f;
	chargeTime = 0;
	chargeShotTime = 0.0f;

	//m_pTexture = CResourceMgr::GetInstance()->LoadTexture("Player", _T("Stage/Player/Player_left.bmp"));
	//m_pTexture->SetColorKey(RGB(255, 255, 255));


	// TEST ---------------------------------------------------

	m_pAnimator = new CAnimator;

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("player_default", _T("Stage/Player/Player.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_LOOP, 2, 1, 0, 0, 1, 0, 1.f);

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("player_moveUp", _T("Stage/Player/Move_TB_A.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 7, 1, 0, 0, 6, 0, 0.5f);

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("player_moveLeft", _T("Stage/Player/Player_left.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 2, 1, 0, 0, 1, 0, 0.3f);

	m_pTexture = CResourceMgr::GetInstance()->LoadTexture("player_moveRight", _T("Stage/Player/Player_right.bmp"));
	m_pTexture->SetColorKey(RGB(255, 255, 255));
	m_pAnimator->AddAnimInfo(m_pTexture, AT_RETAIN, 2, 1, 0, 0, 1, 0, 0.3f);

	// --------------------------------------------------------

}

int CPlayer::Update()
{
	KeyInput();
	CGameObject::UpdateRect();

	//CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY * 76.f/33.f);
	//m_pTexture->SetXY(0.f, 2.f);

	UpdateWingMan();
	UpdateBarrel();
	//m_pTexture->SetXY(0.f, 2.f);


	return NO_EVENT;
}

void CPlayer::Render(HDC hDC)
{
	//m_pTexture->DrawTexture(hDC, m_tImgInfo);

	// TEST ---------------------------------------------------
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	if(CKeyboardMgr::GetInstance()->KeyPressed(KEY_UP))
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 1.f, 76.f / 33.f);
		m_pAnimator->AnimateClip(1, hDC, m_tImgInfo);
	}
	else if(CKeyboardMgr::GetInstance()->KeyPressed(KEY_LEFT))
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 1.f, 1.f);
		m_pAnimator->AnimateClip(2, hDC, m_tImgInfo);
	}
	else if (CKeyboardMgr::GetInstance()->KeyPressed(KEY_RIGHT))
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY, 1.f, 1.f);
		m_pAnimator->AnimateClip(3, hDC, m_tImgInfo);
	}
	else
	{
		CGameObject::UpdateImgInfo(m_tInfo.fCX, m_tInfo.fCY);
		m_pAnimator->AnimateClip(0, hDC, m_tImgInfo);
	}
	// --------------------------------------------------------

	//디버그용
  /*Rectangle(hDC, m_WingManLoc[0].x - 10, m_WingManLoc[0].y - 10, m_WingManLoc[0].x + 10, m_WingManLoc[0].y + 10);
	Rectangle(hDC, m_WingManLoc[1].x - 10, m_WingManLoc[1].y - 10, m_WingManLoc[1].x + 10, m_WingManLoc[1].y + 10);
	Rectangle(hDC, m_WingManLoc[2].x - 10, m_WingManLoc[2].y - 10, m_WingManLoc[2].x + 10, m_WingManLoc[2].y + 10);
	Rectangle(hDC, m_WingManLoc[3].x - 10, m_WingManLoc[3].y - 10, m_WingManLoc[3].x + 10, m_WingManLoc[3].y + 10);*/

	Rectangle(hDC, m_Barrel[0].x - 10, m_Barrel[0].y - 10, m_Barrel[0].x + 10, m_Barrel[0].y + 10);
	Rectangle(hDC, m_Barrel[1].x - 10, m_Barrel[1].y - 10, m_Barrel[1].x + 10, m_Barrel[1].y + 10);
	Rectangle(hDC, m_Barrel[2].x - 10, m_Barrel[2].y - 10, m_Barrel[2].x + 10, m_Barrel[2].y + 10);
	Rectangle(hDC, m_Barrel[3].x - 10, m_Barrel[3].y - 10, m_Barrel[3].x + 10, m_Barrel[3].y + 10);
	Rectangle(hDC, m_Barrel[4].x - 10, m_Barrel[4].y - 10, m_Barrel[4].x + 10, m_Barrel[4].y + 10);

}

void CPlayer::Release()
{
	m_pTexture->SafeDelete();
}

CGameObject* CPlayer::CreateBullet()
{
	return CAbstractFactory<CBullet>::CreateObject(m_tInfo.fX, m_tInfo.fY);
}

CGameObject* CPlayer::CreateBullet(BULLET_DIRECTION eDir, POINT pos,PLAYER_BULLET_TYPE type)
{
	CGameObject* pBullet = CAbstractFactory<CBullet>::CreateObject(pos.x, pos.y);
	dynamic_cast<CBullet*>(pBullet)->SetDirection(eDir);
	dynamic_cast<CBullet*>(pBullet)->SetBulletType(type);
	dynamic_cast<CBullet*>(pBullet)->Initialize();
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
			if(CKeyboardMgr::GetInstance()->KeyPressed(KEY_LEFT))
				m_tInfo.fX -= m_tInfo.fSpeed  * DELTA_TIME;
		}
		if (m_tRect.right < WINCX)
		{
			if (CKeyboardMgr::GetInstance()->KeyPressed(KEY_RIGHT))
				m_tInfo.fX += m_tInfo.fSpeed  * DELTA_TIME;
		}
		if (m_tRect.top > 0)
		{
			if (CKeyboardMgr::GetInstance()->KeyPressed(KEY_UP))
				m_tInfo.fY -= m_tInfo.fSpeed  * DELTA_TIME;		
		}
		if (m_tRect.bottom < WINCY)
		{
			if (CKeyboardMgr::GetInstance()->KeyPressed(KEY_DOWN))
				m_tInfo.fY += m_tInfo.fSpeed  * DELTA_TIME;
		}

		if (CKeyboardMgr::GetInstance()->KeyUp(KEY_ACTION))
		{
			LevelUp();
		}
	static int nMaximumBullet = MAXIMUM_MISSILE;

#pragma region PLAYER_SHOOTING

	if (CKeyboardMgr::GetInstance()->KeyPressed(KEY_SPECIAL))
	{
		//공격버튼을 5초간 누르고, 차지샷 스킬 사용중이 아닐때 ,또한 윙맨의 개수는 2개 이상이어야 차지샷 가능
		if (chargeTime >= 5.f&&m_chargeShot == false&&wingCount>2)
		{
			//윙맨들의 위치를 앞으로 보낸다.
			// 공격버튼에서 손떼기 전까지는 윙맨도 공격하지 않는다.
			m_chargeWIngman = true;
		}
		//그 외에는 연사력만큼 총알을 발사한다.
		else
		{		// 연사력 결정
			if (fFireRate >= 0.1f)
			{
				fFireRate = TIME + 1.f / fFireRate;
				//플레이어 파워레벨 1일경우
				if (m_PowerLevel == 1)
				{
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP,m_Barrel[0],PLAYER_BULLET_TYPE::LEVEL1));
				}
				else if (m_PowerLevel == 2) //2 일경우
				{
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP, m_Barrel[1],PLAYER_BULLET_TYPE::LEVEL1));
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP, m_Barrel[2],PLAYER_BULLET_TYPE::LEVEL1));
				}
				else if (m_PowerLevel == 3) //3일 경우
				{
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP,m_Barrel[0],PLAYER_BULLET_TYPE::LEVEL2));
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP,m_Barrel[1],PLAYER_BULLET_TYPE::LEVEL1));
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP,m_Barrel[2],PLAYER_BULLET_TYPE::LEVEL1));
				}
				else if (m_PowerLevel>=4)// 4일경우
				{
					cout << "LEVEL4" << endl;
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP, m_Barrel[0], PLAYER_BULLET_TYPE::LEVEL4));
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP, m_Barrel[1], PLAYER_BULLET_TYPE::LEVEL3));
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP, m_Barrel[2], PLAYER_BULLET_TYPE::LEVEL3));
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP, m_Barrel[3], PLAYER_BULLET_TYPE::LEVEL2));
					CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP, m_Barrel[4], PLAYER_BULLET_TYPE::LEVEL2));
				}
				if (!m_chargeShot)
				{
					//윙맨들 사격
					for (int i = 0; i < wingCount; ++i)
					{
						dynamic_cast<CWingMan*>(m_WingMan[i])->Fire();
					}
				}
				fFireRate -= fFireRate;
			}
			chargeTime += DELTA_TIME;
			fFireRate += DELTA_TIME;
			cout << chargeTime << endl;
		}

	}
	//공격버튼에서 떼면
	// 2초간 차지 했으면 차지샷 아니면 차지타임 초기화
	if (CKeyboardMgr::GetInstance()->KeyUp(KEY_SPECIAL))
	{
		cout << "공격키 땜" << endl;
		if (m_chargeWIngman)
		{
			m_chargeShot = true;
		}
		chargeTime -= chargeTime;
	}

	if (m_chargeShot)
	{
		//윙맨들은 차지샷 사용시 5초간 그자리에서 발사한다.
		if (chargeShotTime <= 5.0f)
		{
			if (fWingFireRate >= 0.1f)
			{
				for (int i = 0; i < wingCount; ++i)
				{
					dynamic_cast<CWingMan*>(m_WingMan[i])->ChargeShot();
				}
				fWingFireRate -= fWingFireRate;
			}
			fWingFireRate += DELTA_TIME;
			chargeShotTime += DELTA_TIME;
		}
		else
		{
			//5초가 지난후 윙맨들은 자기자리로 돌아가고 
			// 차지스킬샷도 해제
			m_chargeShot = false;
			m_chargeWIngman = false;
			chargeShotTime -= chargeShotTime;
			chargeTime -= chargeTime;
		}
	}
#pragma endregion

	

	//// BUTTON_A : 키보드를 누를 경우 최대 4개의 미사일까지 발사
	//if (!m_bArrButton[BUTTON_A] && (GetAsyncKeyState('A') & 0x8000))
	//{
	//	//CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET,CreateBullet(BULLET_UP));
	//	if (!(--nMaximumBullet))
	//	{
	//		m_bArrButton[BUTTON_A] = true;
	//		nMaximumBullet = MAXIMUM_MISSILE;
	//	}
	//}
	//if (!GetAsyncKeyState('A'))
	//	m_bArrButton[BUTTON_A] = false;

		// BUTTON_S : 필살기 버튼 연속입력 방지
	//	if (!m_bArrButton[BUTTON_S] && (GetAsyncKeyState('S') & 0x8000))
	//	{
	//		CObjectMgr::GetInstance()->AddObject(OBJLECT_BULLET, CreateBullet(BULLET_UP));
	//		//윙맨들 사격
	//		for (int i = 0; i < wingCount; ++i)
	//		{
	//			dynamic_cast<CWingMan*>(m_WingMan[i])->Fire();
	//		}
	//		m_bArrButton[BUTTON_S] = true;
	//		m_bIsAttack = true;
	//	}
	//if (!GetAsyncKeyState('S'))
	//	m_bArrButton[BUTTON_S] = false;
	//if (GetAsyncKeyState('W') & 0x8000)
	//	m_pBulletLst->push_back(CreateBullet(BULLET_UP));
	//if (GetAsyncKeyState('D') & 0x8000)
	//	m_pBulletLst->push_back(CreateBullet(BULLET_RIGHT));
}
