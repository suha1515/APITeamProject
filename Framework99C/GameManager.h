#pragma once
class CGameManager
{
	DECLARE_SINGLE_TONE(CGameManager)

public:
	void SetStageProgress(int _valueY);

public:
	int GetStageProgress();

private:
	void Initialize();

private:
	int m_stageY;

public:
	int m_PlayerLife;
	int m_PlayerBomb;
	int m_Score;
};

