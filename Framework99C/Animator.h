
#pragma once
class CTexture;
class CAnimator
{
public:
	CAnimator();
	~CAnimator();

public:
	void Update();
	bool AddAnimInfo(ANIMINFO animInfo, IMGINFO imgInfo);
	bool AddAnimInfo(CTexture* pTexture, ANIMATION_TYPE animType, float maxX, float maxY,
		float startX, float startY, float endX, float endY, float limitTime);
	bool DeleteAnimInfo(int iIdx);
	void SetImgInfo(int iIdx, IMGINFO& imgInfo);

	void AnimateClip(int iIdx, HDC hDC);
	void AnimateReversedClip(int iIdx, HDC hDC);
	int GetAnimSize();
	CTexture* GetTexture(int iIdx);

private:
	vector<ANIMINFO> m_vecAnimInfo;
};
