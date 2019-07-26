#pragma once
class CEffectMgr
{
	DECLARE_SINGLE_TONE(CEffectMgr)

public:
	void Initialize();
	void AddEffect(EFFECT key);
	void AnimateEffect(HDC hDC, IMGINFO imgInfo);

private:
	unordered_map<EFFECT, ANIMINFO*> m_mapEffect;
	CAnimator* m_pAnimator;
};

