
#pragma once
class CTexture;
class CAnimator
{
public:
	CAnimator();
	~CAnimator();

public:
	void Update();
	bool AddAnimInfo(ANIMINFO animInfo);
	bool AddAnimInfo(CTexture* pTexture, ANIMATION_TYPE animType, float maxX, float maxY,
		float startX, float startY, float endX, float endY, float limitTime);
	bool DeleteAnimInfo(int iIdx);

	void AnimateClip(int iIdx, HDC hDC, const IMGINFO& imgInfo);
	void AnimateReversedClip(int iIdx, HDC hDC, const IMGINFO& imgInfo);
	int GetAnimSize();

private:
	vector<ANIMINFO> m_vecAnimInfo;
};
