#include "stdafx.h"
#include "CollsionMgr.h"
#include "GameObject.h"

DEFINE_SINGLE_TONE(CCollsionMgr)

void CCollsionMgr::Initialize() {};

bool CCollsionMgr::CollisionRect(const OBJLIST& dstLst, const OBJLIST& srcLst)
{
	for (auto& pDest : dstLst)
	{
		for (auto& pSource : srcLst)
		{
			//기저축에 정렬된 충돌 박스 체크 매우 간단한 충돌알고리즘이다.
			RECT dstRect = pDest->GetRect();
			RECT srcRect = pSource->GetRect();
			//x축에 대하여 겹치는지 체크.
			if (dstRect.right - srcRect.left > 0 && srcRect.right - dstRect.left>0)
			{
				//y축에 대하여 겹치는지 체크.
				if (dstRect.bottom - srcRect.top > 0 && srcRect.bottom - dstRect.top>0)
				{
					cout <<"hit colider!" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

bool CCollsionMgr::CollisionRect(const OBJLIST & dstLst, const OBJLIST & srcLst, VECTOR2D* depth)
{
	for (auto& pDest : dstLst)
	{
		for (auto& pSource : srcLst)
		{
			//기저축에 정렬된 충돌 박스 체크 매우 간단한 충돌알고리즘이다.
			RECT dstRect = pDest->GetRect();
			RECT srcRect = pSource->GetRect();
			//x축에 대하여 겹치는지 체크.
			if (dstRect.right - srcRect.left > 0 && srcRect.right - dstRect.left>0)
			{
				//y축에 대하여 겹치는지 체크.
				if (dstRect.bottom - srcRect.top > 0 && srcRect.bottom - dstRect.top>0)
				{
					cout << "hit colider!" << endl;
					//A는 왼쪽 B는 오른쪽
					if (dstRect.right < srcRect.right)
					{
						depth->x = -pDest->GetInfo().fSpeed*DELTA_TIME*fabsf(pSource->GetInfo().fSpeed*DELTA_TIME);
					}
					//A는 오른쪽 B는 왼쪽
					else
					{
						depth->x = pDest->GetInfo().fSpeed*DELTA_TIME*fabsf(pSource->GetInfo().fSpeed*DELTA_TIME);
					}
					//A는 위 B는 아래
					if (dstRect.bottom < srcRect.bottom)
					{
						depth->y = -pDest->GetInfo().fSpeed*DELTA_TIME*fabsf(pSource->GetInfo().fSpeed*DELTA_TIME);
					}
					//A는 아래 B는 위
					else 
					{
						depth->y = pDest->GetInfo().fSpeed*DELTA_TIME*fabsf(pSource->GetInfo().fSpeed*DELTA_TIME);
					}
					return true;
				}
			}
		}
	}
	return false;
}

void CCollsionMgr::CollisionSphere(const OBJLIST& dstLst, const OBJLIST& srcLst)
{
	for (auto& pDest : dstLst)
	{
		for (auto& pSource : srcLst)
		{			
			if (CheckSphere(pDest, pSource))
			{
				pDest->SetDead(true);
				pSource->SetDead(true);
			}
		}
	}
}

bool CCollsionMgr::CheckSphere(const CGameObject* pDest, const CGameObject* pSource)
{
	// 반지름 합
	float fSumRad = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;

	// 중점 간 거리
	float w = pDest->GetInfo().fX - pSource->GetInfo().fX;
	float h = pDest->GetInfo().fY - pSource->GetInfo().fY;

	// 피타고라스	
	float d = sqrtf(w * w + h * h);	

	return d <= fSumRad;
}
