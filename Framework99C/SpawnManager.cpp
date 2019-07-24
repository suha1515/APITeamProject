#include "stdafx.h"
#include "SpawnManager.h"
#include "CommonMonster.h"

CSpawnManager::CSpawnManager()
{

	// 스폰 위치 지정 WINCX=700 이므로 100 씩나누어 700 곳에서 스폰
	for (int i = LEFT_50; i < LOCATION_END; ++i)
	{
		m_SpawnLocation[i].x = (100 * i) + 50;
		// 화면밖에서 스폰한다.
		m_SpawnLocation[i].y = -50;
	}
	
}

CSpawnManager::~CSpawnManager()
{
}

void CSpawnManager::SetEnemyPool(SPAWN_INFO enemy)
{
	m_EnemyPool.push_back(enemy);
}

void CSpawnManager::SpawnEnemy()
{
	list<SPAWN_INFO>::iterator iter_begin = m_EnemyPool.begin();
	list<SPAWN_INFO>::iterator iter_end = m_EnemyPool.end();

	for (; iter_begin != iter_end;)
	{
		SPAWN_INFO info = *iter_begin;
		
		if (info.spawnTime > CGameManager::GetInstance()->GetStageProgress())
		{
			if (info.type == MONSTER_TYPE::DEFAULT)
			{
				CGameObject *object = CAbstractFactory<CCommonMonster>::CreateObject();
				object->SetPos(info.spawnPos_x, info.spawnPos_y);
				dynamic_cast<CCommonMonster*>(object)->SetPlayer(*(CGameObject::m_ObjLst[OBJECT_PLAYER].begin()));
			}
			iter_begin = m_EnemyPool.erase(iter_begin);
		}
		else
		{
			++iter_begin;
		}
	}
}

void CSpawnManager::RenderSpawnLocation()
{

}
