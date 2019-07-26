#pragma once
class CEffectMgr
{
	DECLARE_SINGLE_TONE(CEffectMgr)

public:
	void Initialize();
	CTexture* AddEffect(EFFECT key, IMGINFO imgInfo);
	void AnimateEffect(HDC hDC);

public:
	void DeleteAnimator();
private:
	unordered_map<EFFECT, ANIMINFO*> m_mapEffect;

	CAnimator* m_pAnimator;	
};

