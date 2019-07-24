
#pragma once
class CTexture;
class CAnimator
{
public:
	CAnimator();
	~CAnimator();

public:
	bool AddAnimInfo(ANIMINFO animInfo);
	bool AddAnimInfo(CTexture* pTexture, ANIMATION_TYPE animType, float minX, float minY,
		float maxX, float maxY, float elapsedTime, float limitTime);
	bool DeleteAnimInfo(int iIdx);

	void RunAnim(int iIdx, HDC hDC, IMGINFO& imgInfo);

private:
	vector<ANIMINFO> m_vecAnimInfo;
};
