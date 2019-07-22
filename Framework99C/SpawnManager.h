#pragma once

class CSpawnManager
{
public:
	CSpawnManager();
	~CSpawnManager();

public:
	void SetEnemyPool();
	void SpawnEnemy(int spawnTime);
	void RenderSpawnLocation();


private:
	OBJLIST m_EnemyPool;
	VECTOR2D m_SpawnLocation[7];


};