#pragma once

class CSpawnManager
{
public:
	CSpawnManager();
	~CSpawnManager();

public:
	void SetEnemyPool(SPAWN_INFO* enemy,int size);
	void SpawnEnemy();
	void Initialize();
	void RenderSpawnLocation();


private:
	list<SPAWN_INFO> m_EnemyPool;
	VECTOR2D m_SpawnLocation[7];
};