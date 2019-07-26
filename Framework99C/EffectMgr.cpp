#include "stdafx.h"
#include "EffectMgr.h"

DEFINE_SINGLE_TONE(CEffectMgr)


void CEffectMgr::Initialize()
{
	m_pAnimator = new CAnimator;

	CTexture* pTmpTexture = CResourceMgr::GetInstance()->LoadTexture("MiniPlane_Destroy", _T("Stage/Effect/Effect_2.bmp"));
	pTmpTexture->SetColorKey(RGB(255, 255, 255));
	
	ANIMINFO* pTmpAnim = new ANIMINFO { pTmpTexture , AT_ONCE_DESTROY, 15, 1, 0, 0, 0, 0, 14, 0, 0.f, 0.f, 2.f };
	m_mapEffect.insert(unordered_map<EFFECT, ANIMINFO*>::value_type(E_MINIPLANE_DESTROIED, pTmpAnim));
}

void CEffectMgr::AddEffect(const EFFECT key)
{
	m_pAnimator->AddAnimInfo(*(m_mapEffect[key])); // º¹»çÇØ¼­ ÁÜ
}

void CEffectMgr::AnimateEffect(HDC hDC, IMGINFO imgInfo)
{
	m_pAnimator->Update();
	for (int i = 0; i < m_pAnimator->GetAnimSize(); ++i)
	{
		m_pAnimator->AnimateClip(i, hDC, imgInfo);
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

