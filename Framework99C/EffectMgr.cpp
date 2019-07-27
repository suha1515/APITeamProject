#include "stdafx.h"
#include "EffectMgr.h"

DEFINE_SINGLE_TONE(CEffectMgr)


void CEffectMgr::Initialize()
{
	m_pAnimator = new CAnimator;

	CTexture* pExplosive1 = CResourceMgr::GetInstance()->LoadTexture("Explosive_1_Effect", _T("Stage/Effect/Effect_2.bmp"));
	pExplosive1->SetColorKey(RGB(255, 255, 255));

	CTexture* pHitTexture = CResourceMgr::GetInstance()->LoadTexture("HitEnemy_Effect", _T("Stage/Effect/HitEffect.bmp"));
	pHitTexture->SetColorKey(RGB(0, 255, 0));

	CTexture* pExplosive2= CResourceMgr::GetInstance()->LoadTexture("Explosive_2_Effect", _T("Stage/Effect/Effect_7.bmp"));
	pExplosive2->SetColorKey(RGB(50, 150,200));

	CTexture* pExplosive3 = CResourceMgr::GetInstance()->LoadTexture("Explosive_3_Effect", _T("Stage/Effect/Effect_1.bmp"));
	pExplosive3->SetColorKey(RGB(255, 255, 255));

	

	ANIMINFO* pExplosive_1_Anim = new ANIMINFO(pExplosive1, AT_ONCE_DESTROY, 15, 1, 0, 0, 14, 0, 1.f);
	ANIMINFO* pExplosive_2_Anim = new ANIMINFO(pExplosive2, AT_ONCE_DESTROY, 6, 1, 0, 0, 5, 0, 1.f);
	ANIMINFO* pExplosive_3_Anim = new ANIMINFO(pExplosive3, AT_ONCE_DESTROY, 12, 1, 0, 0, 11, 0, 1.f);
	ANIMINFO* pHitAnim = new ANIMINFO(pHitTexture, AT_ONCE_DESTROY, 17, 1, 0, 0, 16, 0, 1.f);


	m_mapEffect.insert(unordered_map<EFFECT, ANIMINFO*>::value_type(EXPLOSIVE_1, pExplosive_1_Anim));
	m_mapEffect.insert(unordered_map<EFFECT, ANIMINFO*>::value_type(EXPLOSIVE_2, pExplosive_2_Anim));
	m_mapEffect.insert(unordered_map<EFFECT, ANIMINFO*>::value_type(EXPLOSIVE_3, pExplosive_3_Anim));
	m_mapEffect.insert(unordered_map<EFFECT, ANIMINFO*>::value_type(E_HIT_EFFECT, pHitAnim));
}

CTexture* CEffectMgr::AddEffect(const EFFECT key, IMGINFO imgInfo)
{
	m_pAnimator->AddAnimInfo(*(m_mapEffect[key]), imgInfo); // º¹»çÇØ¼­ ÁÜ
	return m_pAnimator->GetTexture(m_pAnimator->GetAnimSize() - 1);
}

void CEffectMgr::AnimateEffect(HDC hDC)
{
	m_pAnimator->Update();

	for (int i = 0; i < m_pAnimator->GetAnimSize(); ++i)
	{
		m_pAnimator->AnimateClip(i, hDC);
	}
}


void CEffectMgr::DeleteAnimator()
{
	if (m_pAnimator)
	{
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
}

