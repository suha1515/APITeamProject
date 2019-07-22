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
			//�����࿡ ���ĵ� �浹 �ڽ� üũ �ſ� ������ �浹�˰����̴�.
			RECT dstRect = pDest->GetRect();
			RECT srcRect = pSource->GetRect();
			//x�࿡ ���Ͽ� ��ġ���� üũ.
			if (dstRect.right - srcRect.left > 0 && srcRect.right - dstRect.left>0)
			{
				//y�࿡ ���Ͽ� ��ġ���� üũ.
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
			//�����࿡ ���ĵ� �浹 �ڽ� üũ �ſ� ������ �浹�˰����̴�.
			RECT dstRect = pDest->GetRect();
			RECT srcRect = pSource->GetRect();
			//x�࿡ ���Ͽ� ��ġ���� üũ.
			if (dstRect.right - srcRect.left > 0 && srcRect.right - dstRect.left>0)
			{
				//y�࿡ ���Ͽ� ��ġ���� üũ.
				if (dstRect.bottom - srcRect.top > 0 && srcRect.bottom - dstRect.top>0)
				{
					float FX = pDest->GetInfo().fX;
					float FY = pDest->GetInfo().fY;
					
					float fx = pDest->GetInfo().fCX*0.5f + pSource->GetInfo().fCX*0.5f;
					float fy = pDest->GetInfo().fCY*0.5f + pSource->GetInfo().fCY*0.5f;
					float depthX =fx-fabs(pDest->GetInfo().fX - pSource->GetInfo().fX);
					float depthY =fy-fabs(pDest->GetInfo().fY - pSource->GetInfo().fY);
					cout << "hit colider!" << endl;

					//x������ ���� �� �� ���. (y���� �δ�)
					if (depthX > depthY)
					{
						//A�� �� B�� �Ʒ�
						if (dstRect.bottom < srcRect.bottom)
						{
							pDest->SetPos(FX, FY - depthY);
						}
						//A�� �Ʒ� B�� ��
						else
						{
							pDest->SetPos(FX, FY + depthY);
						}
					}
					else
					{
						//A�� ���� B�� ������
						if (dstRect.right < srcRect.right)
						{
							pDest->SetPos(FX - depthX, FY);
						}
						//A�� ������ B�� ����
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
	// ������ ��
	float fSumRad = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;

	// ���� �� �Ÿ�
	float w = pDest->GetInfo().fX - pSource->GetInfo().fX;
	float h = pDest->GetInfo().fY - pSource->GetInfo().fY;

	// ��Ÿ���	
	float d = sqrtf(w * w + h * h);	

	return d <= fSumRad;
}
