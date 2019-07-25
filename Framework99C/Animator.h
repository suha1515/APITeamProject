
#pragma once
class CTexture;
class CAnimator
{
public:
	CAnimator();
	~CAnimator();

public:
	bool AddAnimInfo(ANIMINFO animInfo);
	bool AddAnimInfo(CTexture* pTexture, ANIMATION_TYPE animType, float maxX, float maxY,
		float startX, float startY, float endX, float endY, float limitTime);
	bool DeleteAnimInfo(int iIdx);

	void RunAnim(int iIdx, HDC hDC, const IMGINFO& imgInfo);
	void RunReversedAnim(int iIdx, HDC hDC, const IMGINFO& imgInfo);


private:
	vector<ANIMINFO> m_vecAnimInfo;
};
