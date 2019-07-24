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

void CSpawnManager::SetEnemyPool(SPAWN_INFO* enemy)
{
	m_EnemyPool.push_back(enemy);
}

void CSpawnManager::SpawnEnemy()
{
	list<SPAWN_INFO*>::iterator iter_begin = m_EnemyPool.begin();
	list<SPAWN_INFO*>::iterator iter_end = m_EnemyPool.end();

	for (; iter_begin != iter_end;)
	{
		for (int i = 0; i < sizeof((*iter_begin)->enemy) / sizeof(SPAWN_INFO); ++i)
		{
			//���� ��������
		}
		iter_begin = m_EnemyPool.erase(iter_begin);
	}
}

void CSpawnManager::RenderSpawnLocation()
{
}
