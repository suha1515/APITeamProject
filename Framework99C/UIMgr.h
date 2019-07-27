#pragma once
class CUserInterfaceMgr
{
	DECLARE_SINGLE_TONE(CUserInterfaceMgr)

	// CGameObject을(를) 통해 상속됨
	void Initialize();
	void ShowUI(HDC hDC);

public:
	void SetLife(int nLife);
	void SetScore(int nScore);
	void SetSpecial(int nSpecial);

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
