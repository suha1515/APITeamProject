#include "stdafx.h"
#include "SpawnManager.h"
#include "CommonMonster.h"
#include "MidBoss.h"

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

void CSpawnManager::SetEnemyPool(SPAWN_INFO* enemy,int size)
{
	for (int i = 0; i < size; ++i)
	{
		m_EnemyPool.push_back(enemy[i]);
	}
	
}

void CSpawnManager::SpawnEnemy()
{
	list<SPAWN_INFO>::iterator iter_begin = m_EnemyPool.begin();
	list<SPAWN_INFO>::iterator iter_end = m_EnemyPool.end();
	CObjectMgr* objMgr = CObjectMgr::GetInstance();

	for (; iter_begin != iter_end;)
	{
		SPAWN_INFO info = *iter_begin;
		
		if (info.spawnTime > CGameManager::GetInstance()->GetStageProgress())
		{
			if (info.monster_type == MONSTER_TYPE::DEFAULT)
			{
				CGameObject *object = CAbstractFactory<CCommonMonster>::CreateObject();
				object->SetPos(info.spawnPos_x, info.spawnPos_y);
				dynamic_cast<CCommonMonster*>(object)->SetMonType(info.monster_type, info.fire_type, info.move_type,info.monster_various);
				dynamic_cast<CCommonMonster*>(object)->Initialize();
				objMgr->AddObject(OBJECT_MONSTER, object);
			}
			else if (info.monster_type == MONSTER_TYPE::MIDDLE)
			{
				CGameObject *object = CAbstractFactory<CMidBoss>::CreateObject();
				object->SetPos(info.spawnPos_x, info.spawnPos_y);
				dynamic_cast<CMidBoss*>(object)->SetMonType(info.monster_type, info.fire_type, info.move_type, info.monster_various);
				dynamic_cast<CMidBoss*>(object)->Initialize();

				objMgr->AddObject(OBJECT_MONSTER, object);
			}
			iter_begin = m_EnemyPool.erase(iter_begin);
		}
		else
		{
			++iter_begin;
		}
	}
}

void CSpawnManager::Initialize()
{
	//// Monster
	SPAWN_INFO monsterPool[4];
	//
	monsterPool[0].spawnPos_x = 150;
	monsterPool[0].spawnPos_y = -100;
	monsterPool[0].spawnTime = 6500;
	monsterPool[0].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[0].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[0].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[0].monster_various = 0;


	monsterPool[1].spawnPos_x = 250;
	monsterPool[1].spawnPos_y = -100;
	monsterPool[1].spawnTime = 6400;
	monsterPool[1].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[1].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[1].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[1].monster_various = 0;


	monsterPool[2].spawnPos_x = 350;
	monsterPool[2].spawnPos_y = -100;
	monsterPool[2].spawnTime = 6300;
	monsterPool[2].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[2].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[2].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[2].monster_various = 0;

	monsterPool[3].spawnPos_x = 450;
	monsterPool[3].spawnPos_y = -100;
	monsterPool[3].spawnTime = 6200;
	monsterPool[3].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[3].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[3].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[3].monster_various = 3;

	SetEnemyPool(monsterPool, 4);
}

void CSpawnManager::RenderSpawnLocation()
{

}
