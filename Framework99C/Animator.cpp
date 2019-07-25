#include "stdafx.h"
#include "Animator.h"


CAnimator::CAnimator()
{
	m_vecAnimInfo.reserve(10);
}


CAnimator::~CAnimator()
{

}

bool CAnimator::AddAnimInfo(ANIMINFO animInfo)
{
	ANIMINFO tTmpInfo = animInfo;

	m_vecAnimInfo.push_back(tTmpInfo);
	return true;
}

bool CAnimator::AddAnimInfo(CTexture* pTexture, ANIMATION_TYPE animType, float maxX, float maxY,
	float startX, float startY, float endX, float endY, float elapsedTime, float limitTime)
{
	ANIMINFO tTmpInfo;

	tTmpInfo.pTexture = pTexture;
	tTmpInfo.tAnimType = animType;
	tTmpInfo.fMaxX = maxX;
	tTmpInfo.fMaxY = maxY;

	tTmpInfo.fStartX = startX;
	tTmpInfo.fStartY = startY;
	tTmpInfo.fEndX = endX;
	tTmpInfo.fEndY = endY;
	tTmpInfo.fElapsedTime = elapsedTime;
	tTmpInfo.fLimitTime = limitTime;

	m_vecAnimInfo.push_back(tTmpInfo);

	return true;
}

bool CAnimator::DeleteAnimInfo(int iIdx)
{
	int iCurIdx = 0;

	vector<ANIMINFO>::iterator iter;
	vector<ANIMINFO>::iterator iter_end = m_vecAnimInfo.end();

	for (iter = m_vecAnimInfo.begin(); iter != iter_end; )
	{
		if (iCurIdx == iIdx)
		{
			iter = m_vecAnimInfo.erase(iter);
			iter_end = m_vecAnimInfo.end(); // 무효화 방지
		}
		else
		{
			++iter;
			++iCurIdx;
		}
	}

	return true;
}

void CAnimator::RunAnim(int iIdx, HDC hDC, const IMGINFO& imgInfo)
{
	ANIMINFO* tmpAnim = &m_vecAnimInfo.at(iIdx);
	float fUnitTime = tmpAnim->fLimitTime / (tmpAnim->fMaxX);
	float fUnitFrame = 1.f;

	tmpAnim->fElapsedTime += g_fDeltaTime;

	switch (tmpAnim->tAnimType)
	{
	case AT_LOOP:
	{
		if ((tmpAnim->fCurX >= tmpAnim->fEndX) && (tmpAnim->fCurY >= tmpAnim->fEndY))
		{
			tmpAnim->fCurX = tmpAnim->fStartX;
			tmpAnim->fCurY = tmpAnim->fStartY;
		}
	}
	break;
	case AT_RETAIN:
	{
		if ((tmpAnim->fCurX >= tmpAnim->fEndX) && (tmpAnim->fCurY >= tmpAnim->fEndY))
		{
			tmpAnim->fCurX = tmpAnim->fEndX;
			tmpAnim->fCurY = tmpAnim->fEndY;
		}
	}
	break;
	}

	if (tmpAnim->pTexture->m_bColorKeyEnable)
	{
		TransparentBlt(hDC,
			imgInfo.fX - (imgInfo.fImgCX * imgInfo.fPivotX), imgInfo.fY - (imgInfo.fImgCY * imgInfo.fPivotY),
			imgInfo.fImgCX * imgInfo.fScaleX, imgInfo.fImgCY * imgInfo.fScaleY,
			tmpAnim->pTexture->m_hMemDC,
			((tmpAnim->pTexture->m_tBit.bmWidth) / tmpAnim->fMaxX) * tmpAnim->fCurX,
			((tmpAnim->pTexture->m_tBit.bmHeight) / tmpAnim->fMaxY) * tmpAnim->fCurY,
			(tmpAnim->pTexture->m_tBit.bmWidth) / tmpAnim->fMaxX, (tmpAnim->pTexture->m_tBit.bmHeight) / tmpAnim->fMaxY,
			tmpAnim->pTexture->m_tColorKey);
	}
	else
	{
		BitBlt(hDC, imgInfo.fX - (imgInfo.fImgCX * imgInfo.fPivotX), imgInfo.fY - (imgInfo.fImgCY * imgInfo.fPivotY),
			imgInfo.fImgCX, imgInfo.fImgCY, tmpAnim->pTexture->m_hMemDC, imgInfo.fX, imgInfo.fY, SRCCOPY);
	}


	while (tmpAnim->fElapsedTime >= fUnitTime)
	{
		tmpAnim->fCurX += fUnitFrame;

		if (tmpAnim->fCurX > tmpAnim->fEndX)
		{
			tmpAnim->fCurX = tmpAnim->fStartX;
			tmpAnim->fCurY += fUnitFrame;

			if (tmpAnim->fCurY > tmpAnim->fEndY)
			{
				tmpAnim->fCurX = tmpAnim->fEndX;
				tmpAnim->fCurY = tmpAnim->fEndY;
			}
		}
		tmpAnim->fElapsedTime -= fUnitTime;
	}
}

void CAnimator::RunReversedAnim(int iIdx, HDC hDC, const IMGINFO& imgInfo)
{
	ANIMINFO* tmpAnim = &m_vecAnimInfo.at(iIdx);
	float fUnitTime = tmpAnim->fLimitTime / (tmpAnim->fMaxX);
	float fUnitFrame = -1.f;

	tmpAnim->fElapsedTime += g_fDeltaTime;

	switch (tmpAnim->tAnimType)
	{
	case AT_LOOP:
	{
		if ((tmpAnim->fCurX <= tmpAnim->fEndX) && (tmpAnim->fCurY <= tmpAnim->fEndY))
		{
			tmpAnim->fCurX = tmpAnim->fStartX;
			tmpAnim->fCurY = tmpAnim->fStartY;
		}
	}
	break;
	case AT_RETAIN:
	{
		if ((tmpAnim->fCurX <= tmpAnim->fEndX) && (tmpAnim->fCurY <= tmpAnim->fEndY))
		{
			tmpAnim->fCurX = tmpAnim->fEndX;
			tmpAnim->fCurY = tmpAnim->fEndY;
		}
	}
	break;
	}

	if (tmpAnim->pTexture->m_bColorKeyEnable)
	{
		TransparentBlt(hDC,
			imgInfo.fX - (imgInfo.fImgCX * imgInfo.fPivotX), imgInfo.fY - (imgInfo.fImgCY * imgInfo.fPivotY),
			imgInfo.fImgCX * imgInfo.fScaleX, imgInfo.fImgCY * imgInfo.fScaleY,
			tmpAnim->pTexture->m_hMemDC,
			((tmpAnim->pTexture->m_tBit.bmWidth) / tmpAnim->fMaxX) * tmpAnim->fCurX,
			((tmpAnim->pTexture->m_tBit.bmHeight) / tmpAnim->fMaxY) * tmpAnim->fCurY,
			(tmpAnim->pTexture->m_tBit.bmWidth) / tmpAnim->fMaxX, (tmpAnim->pTexture->m_tBit.bmHeight) / tmpAnim->fMaxY,
			tmpAnim->pTexture->m_tColorKey);
	}
	else
	{
		BitBlt(hDC, imgInfo.fX - (imgInfo.fImgCX * imgInfo.fPivotX), imgInfo.fY - (imgInfo.fImgCY * imgInfo.fPivotY),
			imgInfo.fImgCX, imgInfo.fImgCY, tmpAnim->pTexture->m_hMemDC, imgInfo.fX, imgInfo.fY, SRCCOPY);
	}


	while (tmpAnim->fElapsedTime >= fUnitTime)
	{
		tmpAnim->fCurX += fUnitFrame;

		if (tmpAnim->fCurX < tmpAnim->fEndX)
		{
			tmpAnim->fCurX = tmpAnim->fStartX;
			tmpAnim->fCurY += fUnitFrame;

			if (tmpAnim->fCurY < tmpAnim->fEndY)
			{
				tmpAnim->fCurX = tmpAnim->fEndX;
				tmpAnim->fCurY = tmpAnim->fEndY;
			}
		}
		tmpAnim->fElapsedTime -= fUnitTime;
	}
}