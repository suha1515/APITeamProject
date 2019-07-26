#pragma once
#include "GameObject.h"
class CUserInterface :
	public CGameObject
{
public:
	CUserInterface();
	virtual ~CUserInterface();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	void SetLife(int nLife);
	void SetScore(int nScore);
	void AddSpecial();
	void SubSpecial();

private:
	int CalModular(int& number, int digit);

private:
	int m_nScore = 5252; // test
	int m_nNumOfSpecial;
	int m_nNumOfLife;

	CTexture* m_pTextureBoob;
	CTexture* m_pTextureLife;
	CTexture* m_pTextureScore;
};

