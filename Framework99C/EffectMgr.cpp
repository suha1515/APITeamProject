#include "stdafx.h"
#include "EffectMgr.h"

DEFINE_SINGLE_TONE(CEffectMgr)


void CEffectMgr::Initialize()
{
	m_pAnimator = new CAnimator;

	CTexture* pTmpTexture = CResourceMgr::GetInstance()->LoadTexture("MiniPlane_Destroy", _T("Stage/Effect/Effect_2.bmp"));
	pTmpTexture->SetColorKey(RGB(255, 255, 255));
	
	ANIMINFO* pTmpAnim = new ANIMINFO(pTmpTexture , AT_ONCE_DESTROY, 15, 1, 0, 0, 14, 0, 2.f);
	m_mapEffect.insert(unordered_map<EFFECT, ANIMINFO*>::value_type(E_MINIPLANE_DESTROIED, pTmpAnim));
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

