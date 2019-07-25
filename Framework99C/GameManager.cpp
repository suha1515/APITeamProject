#include "stdafx.h"
#include "GameManager.h"

DEFINE_SINGLE_TONE(CGameManager)

void CGameManager::SetStageProgress(int _valueY)
{
	m_stageY = _valueY;
}

int CGameManager::GetStageProgress()
{
	return m_stageY;
}
void CGameManager::Initialize() {};
