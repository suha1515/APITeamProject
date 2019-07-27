#include "stdafx.h"
#include "SpawnManager.h"
#include "CommonMonster.h"
#include "MidBoss.h"
#include "Boss.h"

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
				CGameObject *object = new CCommonMonster;
				object->SetPos(info.spawnPos_x, info.spawnPos_y);
				dynamic_cast<CCommonMonster*>(object)->SetMonType(info.monster_type, info.fire_type, info.move_type,info.monster_various);
				dynamic_cast<CCommonMonster*>(object)->Initialize();
				objMgr->AddObject(OBJECT_MONSTER, object);
			}
			else if (info.monster_type == MONSTER_TYPE::MIDDLE)
			{
				CGameObject *object = new CMidBoss;
				object->SetPos(info.spawnPos_x, info.spawnPos_y);
				dynamic_cast<CMidBoss*>(object)->SetMonType(info.monster_type, info.fire_type, info.move_type, info.monster_various);
				dynamic_cast<CMidBoss*>(object)->Initialize();

				objMgr->AddObject(OBJECT_MONSTER, object);
			}
			else if (info.monster_type == MONSTER_TYPE::BOSS)
			{
				CGameObject *object = new CBoss;
				object->SetPos(info.spawnPos_x, info.spawnPos_y);
				dynamic_cast<CBoss*>(object)->SetMonType(info.monster_type, info.fire_type, info.move_type, info.monster_various);
				dynamic_cast<CBoss*>(object)->Initialize();

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
	SPAWN_INFO monsterPool[84];
	//1번 웨이브
	// 잡몹
	monsterPool[0].spawnPos_x = 150;
	monsterPool[0].spawnPos_y = -100;
	monsterPool[0].spawnTime = 6500;
	monsterPool[0].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[0].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[0].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[0].monster_various = 0;

	monsterPool[1].spawnPos_x = 250;
	monsterPool[1].spawnPos_y = -100;
	monsterPool[1].spawnTime = 6450;
	monsterPool[1].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[1].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[1].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[1].monster_various = 0;

	monsterPool[2].spawnPos_x = 350;
	monsterPool[2].spawnPos_y = -100;
	monsterPool[2].spawnTime = 6400;
	monsterPool[2].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[2].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[2].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[2].monster_various = 0;

	monsterPool[3].spawnPos_x = 450;
	monsterPool[3].spawnPos_y = -100;
	monsterPool[3].spawnTime = 6350;
	monsterPool[3].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[3].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[3].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[3].monster_various = 3;	// drop

	// 2번 웨이브
	// 중몹
	monsterPool[4].spawnPos_x = 200;
	monsterPool[4].spawnPos_y = -100;
	monsterPool[4].spawnTime = 6000;
	monsterPool[4].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[4].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[4].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[4].monster_various = 0;

	monsterPool[5].spawnPos_x = 500;
	monsterPool[5].spawnPos_y = -100;
	monsterPool[5].spawnTime = 5500;
	monsterPool[5].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[5].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[5].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[5].monster_various = 0;

	//잡몹
	monsterPool[6].spawnPos_x = 100;
	monsterPool[6].spawnPos_y = -100;
	monsterPool[6].spawnTime = 5700;
	monsterPool[6].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[6].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[6].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[6].monster_various = 3;	// drop

	monsterPool[7].spawnPos_x = 150;
	monsterPool[7].spawnPos_y = -100;
	monsterPool[7].spawnTime = 5750;
	monsterPool[7].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[7].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[7].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[7].monster_various = 0;

	monsterPool[8].spawnPos_x = 200;
	monsterPool[8].spawnPos_y = -100;
	monsterPool[8].spawnTime = 5800;
	monsterPool[8].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[8].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[8].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[8].monster_various = 0;

	monsterPool[9].spawnPos_x = 250;
	monsterPool[9].spawnPos_y = -100;
	monsterPool[9].spawnTime = 5850;
	monsterPool[9].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[9].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[9].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[9].monster_various = 0;

	monsterPool[10].spawnPos_x = 300;
	monsterPool[10].spawnPos_y = -100;
	monsterPool[10].spawnTime = 5900;
	monsterPool[10].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[10].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[10].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[10].monster_various = 0;

	// 2-2웨이브 잡몹
	monsterPool[11].spawnPos_x = 400;
	monsterPool[11].spawnPos_y = -100;
	monsterPool[11].spawnTime = 5600;
	monsterPool[11].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[11].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[11].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[11].monster_various = 1;

	monsterPool[12].spawnPos_x = 450;
	monsterPool[12].spawnPos_y = -100;
	monsterPool[12].spawnTime = 5550;
	monsterPool[12].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[12].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[12].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[12].monster_various = 1;

	monsterPool[13].spawnPos_x = 500;
	monsterPool[13].spawnPos_y = -100;
	monsterPool[13].spawnTime = 5500;
	monsterPool[13].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[13].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[13].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[13].monster_various = 1;


	// 3번 웨이브
	//중몹
	monsterPool[14].spawnPos_x = 350;
	monsterPool[14].spawnPos_y = -100;
	monsterPool[14].spawnTime = 5200;
	monsterPool[14].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[14].fire_type = MONSTER_FIRETYPE::BRUST_3;
	monsterPool[14].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[14].monster_various = 2;
	//잡몹
	monsterPool[15].spawnPos_x = 50;
	monsterPool[15].spawnPos_y = -100;
	monsterPool[15].spawnTime = 5150;
	monsterPool[15].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[15].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[15].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[15].monster_various = 1;

	monsterPool[16].spawnPos_x = 100;
	monsterPool[16].spawnPos_y = -100;
	monsterPool[16].spawnTime = 5150;
	monsterPool[16].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[16].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[16].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[16].monster_various = 1;

	monsterPool[17].spawnPos_x = 150;
	monsterPool[17].spawnPos_y = -100;
	monsterPool[17].spawnTime = 5150;
	monsterPool[17].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[17].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[17].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[17].monster_various = 2;

	monsterPool[18].spawnPos_x = 550;
	monsterPool[18].spawnPos_y = -100;
	monsterPool[18].spawnTime = 5150;
	monsterPool[18].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[18].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[18].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[18].monster_various = 2;

	monsterPool[19].spawnPos_x = 600;
	monsterPool[19].spawnPos_y = -100;
	monsterPool[19].spawnTime = 5150;
	monsterPool[19].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[19].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[19].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[19].monster_various = 1;

	monsterPool[20].spawnPos_x = 650;
	monsterPool[20].spawnPos_y = -100;
	monsterPool[20].spawnTime = 5150;
	monsterPool[20].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[20].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[20].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[20].monster_various = 3;	// drop
	// 잡몹 3-2웨이브(중몹 상대하면서 추가지원)
	monsterPool[21].spawnPos_x = 100;
	monsterPool[21].spawnPos_y = -100;
	monsterPool[21].spawnTime = 5000;
	monsterPool[21].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[21].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[21].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[21].monster_various = 2;

	monsterPool[22].spawnPos_x = 200;
	monsterPool[22].spawnPos_y = -100;
	monsterPool[22].spawnTime = 4950;
	monsterPool[22].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[22].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[22].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[22].monster_various = 2;

	monsterPool[23].spawnPos_x = 300;
	monsterPool[23].spawnPos_y = -100;
	monsterPool[23].spawnTime = 4900;
	monsterPool[23].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[23].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[23].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[23].monster_various = 2;

	monsterPool[24].spawnPos_x = 400;
	monsterPool[24].spawnPos_y = -100;
	monsterPool[24].spawnTime = 4850;
	monsterPool[24].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[24].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[24].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[24].monster_various = 2;

	monsterPool[25].spawnPos_x = 500;
	monsterPool[25].spawnPos_y = -100;
	monsterPool[25].spawnTime = 4800;
	monsterPool[25].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[25].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[25].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[25].monster_various = 2;

	monsterPool[26].spawnPos_x = 600;
	monsterPool[26].spawnPos_y = -100;
	monsterPool[26].spawnTime = 4750;
	monsterPool[26].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[26].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[26].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[26].monster_various = 2;
	// 잡몹 3-3(요격조)
	monsterPool[27].spawnPos_x = 600;
	monsterPool[27].spawnPos_y = -100;
	monsterPool[27].spawnTime = 4700;
	monsterPool[27].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[27].fire_type = MONSTER_FIRETYPE::AUTO;
	monsterPool[27].move_type = MONSTER_MOVETYPE::TO_PLAYERX;
	monsterPool[27].monster_various = 0;

	monsterPool[28].spawnPos_x = 650;
	monsterPool[28].spawnPos_y = -100;
	monsterPool[28].spawnTime = 4600;
	monsterPool[28].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[28].fire_type = MONSTER_FIRETYPE::AUTO;
	monsterPool[28].move_type = MONSTER_MOVETYPE::TO_PLAYERX;
	monsterPool[28].monster_various = 0;

	monsterPool[29].spawnPos_x = 550;
	monsterPool[29].spawnPos_y = -100;
	monsterPool[29].spawnTime = 4680;
	monsterPool[29].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[29].fire_type = MONSTER_FIRETYPE::AUTO;
	monsterPool[29].move_type = MONSTER_MOVETYPE::TO_PLAYERX;
	monsterPool[29].monster_various = 3;

	// 4웨이브
	// 중몹
	monsterPool[30].spawnPos_x = 550;
	monsterPool[30].spawnPos_y = -100;
	monsterPool[30].spawnTime = 4200;
	monsterPool[30].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[30].fire_type = MONSTER_FIRETYPE::AUTO;
	monsterPool[30].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[30].monster_various = 1;

	monsterPool[31].spawnPos_x = 150;
	monsterPool[31].spawnPos_y = -100;
	monsterPool[31].spawnTime = 4000;
	monsterPool[31].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[31].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[31].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[31].monster_various = 0;
	// 4웨이브 잡몹1(우측에서 출현, 좌향)
	monsterPool[32].spawnPos_x = 650;
	monsterPool[32].spawnPos_y = -100;
	monsterPool[32].spawnTime = 4200;
	monsterPool[32].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[32].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[32].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[32].monster_various = 0;

	monsterPool[33].spawnPos_x = 650;
	monsterPool[33].spawnPos_y = -100;
	monsterPool[33].spawnTime = 4150;
	monsterPool[33].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[33].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[33].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[33].monster_various = 0;

	monsterPool[34].spawnPos_x = 600;
	monsterPool[34].spawnPos_y = -100;
	monsterPool[34].spawnTime = 4100;
	monsterPool[34].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[34].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[34].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[34].monster_various = 0;

	monsterPool[35].spawnPos_x = 550;
	monsterPool[35].spawnPos_y = -100;
	monsterPool[35].spawnTime = 4050;
	monsterPool[35].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[35].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[35].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[35].monster_various = 0;

	monsterPool[36].spawnPos_x = 500;
	monsterPool[36].spawnPos_y = -100;
	monsterPool[36].spawnTime = 4000;
	monsterPool[36].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[36].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[36].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[36].monster_various = 0;

	monsterPool[37].spawnPos_x = 450;
	monsterPool[37].spawnPos_y = -100;
	monsterPool[37].spawnTime = 3950;
	monsterPool[37].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[37].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[37].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[37].monster_various = 3;	// drop

	// 4-2 잡몹(좌측출현, 우향)
	monsterPool[38].spawnPos_x = 50;
	monsterPool[38].spawnPos_y = -100;
	monsterPool[38].spawnTime = 4000;
	monsterPool[38].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[38].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[38].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[38].monster_various = 0;

	monsterPool[39].spawnPos_x = 100;
	monsterPool[39].spawnPos_y = -100;
	monsterPool[39].spawnTime = 3950;
	monsterPool[39].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[39].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[39].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[39].monster_various = 0;

	monsterPool[40].spawnPos_x = 150;
	monsterPool[40].spawnPos_y = -100;
	monsterPool[40].spawnTime = 3900;
	monsterPool[40].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[40].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[40].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[40].monster_various = 0;

	monsterPool[41].spawnPos_x = 200;
	monsterPool[41].spawnPos_y = -100;
	monsterPool[41].spawnTime = 3850;
	monsterPool[41].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[41].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[41].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[41].monster_various = 0;

	monsterPool[42].spawnPos_x = 250;
	monsterPool[42].spawnPos_y = -100;
	monsterPool[42].spawnTime = 3800;
	monsterPool[42].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[42].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[42].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[42].monster_various = 0;

	monsterPool[43].spawnPos_x = 300;
	monsterPool[43].spawnPos_y = -100;
	monsterPool[43].spawnTime = 3750;
	monsterPool[43].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[43].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[43].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[43].monster_various = 3;	// drop

	// 4-3 잡몹
	monsterPool[44].spawnPos_x = 200;
	monsterPool[44].spawnPos_y = -100;
	monsterPool[44].spawnTime = 3900;
	monsterPool[44].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[44].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[44].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[44].monster_various = 2;

	monsterPool[45].spawnPos_x = 300;
	monsterPool[45].spawnPos_y = -100;
	monsterPool[45].spawnTime = 3850;
	monsterPool[45].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[45].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[45].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[45].monster_various = 2;

	monsterPool[46].spawnPos_x = 500;
	monsterPool[46].spawnPos_y = -100;
	monsterPool[46].spawnTime = 3900;
	monsterPool[46].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[46].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[46].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[46].monster_various = 2;

	monsterPool[47].spawnPos_x = 400;
	monsterPool[47].spawnPos_y = -100;
	monsterPool[47].spawnTime = 3850;
	monsterPool[47].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[47].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[47].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[47].monster_various = 2;

	// 5wave
	// m
	monsterPool[48].spawnPos_x = 500;
	monsterPool[48].spawnPos_y = -100;
	monsterPool[48].spawnTime = 2550;
	monsterPool[48].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[48].fire_type = MONSTER_FIRETYPE::AUTO;
	monsterPool[48].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[48].monster_various = 3;

	monsterPool[49].spawnPos_x = 500;
	monsterPool[49].spawnPos_y = -100;
	monsterPool[49].spawnTime = 2900;
	monsterPool[49].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[49].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[49].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[49].monster_various = 0;

	monsterPool[50].spawnPos_x = 500;
	monsterPool[50].spawnPos_y = -100;
	monsterPool[50].spawnTime = 2900;
	monsterPool[50].monster_type = MONSTER_TYPE::MIDDLE;
	monsterPool[50].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[50].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[50].monster_various = 0;

	//5-1s 중몹 출현과 동시에(좌측)
	monsterPool[51].spawnPos_x = 100;
	monsterPool[51].spawnPos_y = -100;
	monsterPool[51].spawnTime = 2950;
	monsterPool[51].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[51].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[51].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[51].monster_various = 0;

	monsterPool[52].spawnPos_x = 150;
	monsterPool[52].spawnPos_y = -100;
	monsterPool[52].spawnTime = 2900;
	monsterPool[52].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[52].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[52].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[52].monster_various = 0;

	monsterPool[53].spawnPos_x = 200;
	monsterPool[53].spawnPos_y = -100;
	monsterPool[53].spawnTime = 2850;
	monsterPool[53].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[53].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[53].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[53].monster_various = 3;

	monsterPool[54].spawnPos_x = 150;
	monsterPool[54].spawnPos_y = -100;
	monsterPool[54].spawnTime = 2800;
	monsterPool[54].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[54].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[54].move_type = MONSTER_MOVETYPE::TO_PLAYERX;
	monsterPool[54].monster_various = 2;

	//5-2s 1번조 돌격 후 추가투입(우측)
	monsterPool[55].spawnPos_x = 600;
	monsterPool[55].spawnPos_y = -100;
	monsterPool[55].spawnTime = 2900;
	monsterPool[55].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[55].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[55].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[55].monster_various = 0;

	monsterPool[56].spawnPos_x = 550;
	monsterPool[56].spawnPos_y = -100;
	monsterPool[56].spawnTime = 2850;
	monsterPool[56].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[56].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[56].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[56].monster_various = 0;

	monsterPool[57].spawnPos_x =500;
	monsterPool[57].spawnPos_y = -100;
	monsterPool[57].spawnTime = 2800;
	monsterPool[57].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[57].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[57].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[57].monster_various = 0;

	monsterPool[58].spawnPos_x = 450;
	monsterPool[58].spawnPos_y = -100;
	monsterPool[58].spawnTime = 2750;
	monsterPool[58].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[58].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[58].move_type = MONSTER_MOVETYPE::TO_PLAYERX;
	monsterPool[58].monster_various = 2;

	// 5-3s
	monsterPool[59].spawnPos_x = 250;
	monsterPool[59].spawnPos_y = -100;
	monsterPool[59].spawnTime = 2500;
	monsterPool[59].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[59].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[59].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[59].monster_various = 0;

	monsterPool[60].spawnPos_x = 300;
	monsterPool[60].spawnPos_y = -100;
	monsterPool[60].spawnTime = 2450;
	monsterPool[60].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[60].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[60].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[60].monster_various = 0;

	monsterPool[61].spawnPos_x = 350;
	monsterPool[61].spawnPos_y = -100;
	monsterPool[61].spawnTime = 2400;
	monsterPool[61].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[61].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[61].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[61].monster_various = 0;

	monsterPool[62].spawnPos_x = 400;
	monsterPool[62].spawnPos_y = -100;
	monsterPool[62].spawnTime = 2350;
	monsterPool[62].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[62].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[62].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[62].monster_various = 0;

	// 5-4s
	monsterPool[63].spawnPos_x = 650;
	monsterPool[63].spawnPos_y = -100;
	monsterPool[63].spawnTime = 2400;
	monsterPool[63].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[63].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[63].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[63].monster_various = 0;

	monsterPool[64].spawnPos_x = 600;
	monsterPool[64].spawnPos_y = -100;
	monsterPool[64].spawnTime = 2350;
	monsterPool[64].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[64].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[64].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[64].monster_various = 0;

	monsterPool[65].spawnPos_x = 550;
	monsterPool[65].spawnPos_y = -100;
	monsterPool[65].spawnTime = 2300;
	monsterPool[65].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[65].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[65].move_type = MONSTER_MOVETYPE::RIGHT;
	monsterPool[65].monster_various = 0;

	monsterPool[66].spawnPos_x = 50;
	monsterPool[66].spawnPos_y = -100;
	monsterPool[66].spawnTime = 2400;
	monsterPool[66].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[66].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[66].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[66].monster_various = 0;

	monsterPool[67].spawnPos_x = 100;
	monsterPool[67].spawnPos_y = -100;
	monsterPool[67].spawnTime = 2350;
	monsterPool[67].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[67].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[67].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[67].monster_various = 0;

	monsterPool[68].spawnPos_x = 150;
	monsterPool[68].spawnPos_y = -100;
	monsterPool[68].spawnTime = 2300;
	monsterPool[68].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[68].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[68].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[68].monster_various = 0;

	// 첫웨이브 잡몹 추가
	monsterPool[69].spawnPos_x = 550;
	monsterPool[69].spawnPos_y = -100;
	monsterPool[69].spawnTime = 6300;
	monsterPool[69].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[69].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[69].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[69].monster_various = 0;

	monsterPool[70].spawnPos_x = 500;
	monsterPool[70].spawnPos_y = -100;
	monsterPool[70].spawnTime = 6250;
	monsterPool[70].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[70].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[70].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[70].monster_various = 0;

	monsterPool[71].spawnPos_x = 450;
	monsterPool[71].spawnPos_y = -100;
	monsterPool[71].spawnTime = 6200;
	monsterPool[71].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[71].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[71].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[71].monster_various = 0;

	monsterPool[72].spawnPos_x = 400;
	monsterPool[72].spawnPos_y = -100;
	monsterPool[72].spawnTime = 6150;
	monsterPool[72].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[72].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[72].move_type = MONSTER_MOVETYPE::LEFT;
	monsterPool[72].monster_various = 3;	// drop

	// 보스전 마지막 잡몹때 출현
	monsterPool[73].spawnPos_x = 650;
	monsterPool[73].spawnPos_y = -100;
	monsterPool[73].spawnTime = 1900;
	monsterPool[73].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[73].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[73].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[73].monster_various = 0;

	monsterPool[74].spawnPos_x = 600;
	monsterPool[74].spawnPos_y = -100;
	monsterPool[74].spawnTime = 1850;
	monsterPool[74].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[74].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[74].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[74].monster_various = 0;

	monsterPool[75].spawnPos_x = 550;
	monsterPool[75].spawnPos_y = -100;
	monsterPool[75].spawnTime = 1800;
	monsterPool[75].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[75].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[75].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[75].monster_various = 0;

	monsterPool[76].spawnPos_x = 50;
	monsterPool[76].spawnPos_y = -100;
	monsterPool[76].spawnTime = 1800;
	monsterPool[76].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[76].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[76].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[76].monster_various = 0;

	monsterPool[77].spawnPos_x = 100;
	monsterPool[77].spawnPos_y = -100;
	monsterPool[77].spawnTime = 1750;
	monsterPool[77].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[77].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[77].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[77].monster_various = 0;

	monsterPool[78].spawnPos_x = 150;
	monsterPool[78].spawnPos_y = -100;
	monsterPool[78].spawnTime = 1700;
	monsterPool[78].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[78].fire_type = MONSTER_FIRETYPE::BOMBING;
	monsterPool[78].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[78].monster_various = 0;

	monsterPool[79].spawnPos_x = 200;
	monsterPool[79].spawnPos_y = -100;
	monsterPool[79].spawnTime = 1850;
	monsterPool[79].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[79].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[79].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[79].monster_various = 2;

	monsterPool[80].spawnPos_x = 250;
	monsterPool[80].spawnPos_y = -100;
	monsterPool[80].spawnTime = 1800;
	monsterPool[80].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[80].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[80].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[80].monster_various = 2;

	monsterPool[81].spawnPos_x = 300;
	monsterPool[81].spawnPos_y = -100;
	monsterPool[81].spawnTime = 1750;
	monsterPool[81].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[81].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[81].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[81].monster_various = 2;

	monsterPool[82].spawnPos_x = 350;
	monsterPool[82].spawnPos_y = -100;
	monsterPool[82].spawnTime = 1700;
	monsterPool[82].monster_type = MONSTER_TYPE::DEFAULT;
	monsterPool[82].fire_type = MONSTER_FIRETYPE::BRUST_2;
	monsterPool[82].move_type = MONSTER_MOVETYPE::WAVING;
	monsterPool[82].monster_various = 3;

	// 보스출현
	monsterPool[83].spawnPos_x = 375;
	monsterPool[83].spawnPos_y = -300;
	monsterPool[83].spawnTime = 1600;
	monsterPool[83].monster_type = MONSTER_TYPE::BOSS;
	monsterPool[83].fire_type = MONSTER_FIRETYPE::SINGLE;
	monsterPool[83].move_type = MONSTER_MOVETYPE::DOWN;
	monsterPool[83].monster_various = 0;


	SetEnemyPool(monsterPool, 84);
}

void CSpawnManager::RenderSpawnLocation()
{

}
