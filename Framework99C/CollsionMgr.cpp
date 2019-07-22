#include "stdafx.h"
#include "CollsionMgr.h"
#include "GameObject.h"

CCollsionMgr::CCollsionMgr()
{
}


CCollsionMgr::~CCollsionMgr()
{
}

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

bool CCollsionMgr::CollisionRectEX(const OBJLIST & dstLst, const OBJLIST & srcLst)
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
					float FX = pDest->GetInfo().fX;
					float FY = pDest->GetInfo().fY;
					
					float fx = pDest->GetInfo().fCX*0.5f + pSource->GetInfo().fCX*0.5f;
					float fy = pDest->GetInfo().fCY*0.5f + pSource->GetInfo().fCY*0.5f;
					float depthX =fx-fabs(pDest->GetInfo().fX - pSource->GetInfo().fX);
					float depthY =fy-fabs(pDest->GetInfo().fY - pSource->GetInfo().fY);
					cout << "hit colider!" << endl;

					//x축으로 깊이 더 들어갈 경우. (y축을 민다)
					if (depthX > depthY)
					{
						//A는 위 B는 아래
						if (dstRect.bottom < srcRect.bottom)
						{
							pDest->SetPos(FX, FY - depthY);
						}
						//A는 아래 B는 위
						else
						{
							pDest->SetPos(FX, FY + depthY);
						}
					}
					else
					{
						//A는 왼쪽 B는 오른쪽
						if (dstRect.right < srcRect.right)
						{
							pDest->SetPos(FX - depthX, FY);
						}
						//A는 오른쪽 B는 왼쪽
						else
						{
							pDest->SetPos(FX + depthX, FY);
						}

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
