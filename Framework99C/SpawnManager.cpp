#include "stdafx.h"
#include "SpawnManager.h"

CSpawnManager::CSpawnManager()
{

	// ���� ��ġ ���� WINCX=700 �̹Ƿ� 100 �������� 700 ������ ����
	for (int i = LEFT_50; i < LOCATION_END; ++i)
	{
		m_SpawnLocation[i].x = (100 * i) + 50;
		// ȭ��ۿ��� �����Ѵ�.
		m_SpawnLocation[i].y = -50;
	}
	
}

CSpawnManager::~CSpawnManager()
{
}

void CSpawnManager::SetEnemyPool()
{
}

void CSpawnManager::SpawnEnemy(int spawnTime)
{

}

void CSpawnManager::RenderSpawnLocation()
{
}
