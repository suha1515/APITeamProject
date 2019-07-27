#include "stdafx.h"
#include "UIMgr.h"

DEFINE_SINGLE_TONE(CUserInterfaceMgr)

void CUserInterfaceMgr::Initialize()
{
	m_nNumOfLife = 2;
	m_nNumOfSpecial = 2;

	m_pTextureBoob = CResourceMgr::GetInstance()->LoadTexture("UI_Bomb", _T("Stage/Item/Item_Bomb.bmp"));
	m_pTextureBoob->SetColorKey(RGB(0, 128, 128));

	m_pTextureLife = CResourceMgr::GetInstance()->LoadTexture("player_moveLeft", _T("Stage/Player/Player_left.bmp"));
	m_pTextureLife->SetColorKey(RGB(255, 255, 255));

	m_pTextureScore = CResourceMgr::GetInstance()->LoadTexture("Score", _T("Stage/Score/Score.bmp"));
	m_pTextureScore->SetColorKey(RGB(255, 40, 255));
}

void CUserInterfaceMgr::ShowUI(HDC hDC)
{
	int nTmpScore = m_nScore;
	int nTmpResult = 0;

	for (int i = 0; i <= 5; ++i)
	{
		nTmpResult = 0;
		nTmpResult = CalModular(nTmpScore, pow(10, 5 - i));

		if (nTmpResult != nTmpScore || nTmpResult < 10)
		{
			m_pTextureScore->DrawTexture(hDC, IMGINFO(40 * i, 0, 0, 0, 47, 47), 0, 47 * nTmpResult, 1, 10);
		}
	}


	for (int i = 1; i <= m_nNumOfLife; ++i)
	{
		m_pTextureLife->DrawTexture(hDC, IMGINFO(40 * i, 50, 0, 0, 40, 40), 0, 0, 2, 1);
	}


	for (int i = 1; i <= m_nNumOfSpecial; ++i)
	{
		m_pTextureBoob->DrawTexture(hDC, IMGINFO(60 * i, WINCY - 50, 0, 0, 54, 32), 54, 0, 4, 1);
	}
}


void CUserInterfaceMgr::SetLife(int nLife)
{
	m_nNumOfLife = nLife;
}

void CUserInterfaceMgr::SetScore(int nScore)
{
	m_nScore = nScore;
}

void CUserInterfaceMgr::AddSpecial()
{
	++m_nNumOfSpecial;
}

void CUserInterfaceMgr::SubSpecial()
{
	--m_nNumOfSpecial;
}

int CUserInterfaceMgr::CalModular(int& number, int digit)
{
	int nTmp = number / digit;
	number %= digit;

	return nTmp;
}