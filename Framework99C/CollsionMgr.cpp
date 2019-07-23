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

bool CCollsionMgr::CollisionRect(const OBJLIST & dstLst, const OBJLIST & srcLst, VECTOR2D* depth)
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
					cout << "hit colider!" << endl;
					//A�� ���� B�� ������
					if (dstRect.right < srcRect.right)
					{
						depth->x = -pDest->GetInfo().fSpeed*DELTA_TIME*fabsf(pSource->GetInfo().fSpeed*DELTA_TIME);
					}
					//A�� ������ B�� ����
					else
					{
						depth->x = pDest->GetInfo().fSpeed*DELTA_TIME*fabsf(pSource->GetInfo().fSpeed*DELTA_TIME);
					}
					//A�� �� B�� �Ʒ�
					if (dstRect.bottom < srcRect.bottom)
					{
						depth->y = -pDest->GetInfo().fSpeed*DELTA_TIME*fabsf(pSource->GetInfo().fSpeed*DELTA_TIME);
					}
					//A�� �Ʒ� B�� ��
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
	// ������ ��
	float fSumRad = pDest->GetInfo().fCX * 0.5f + pSource->GetInfo().fCX * 0.5f;

	// ���� �� �Ÿ�
	float w = pDest->GetInfo().fX - pSource->GetInfo().fX;
	float h = pDest->GetInfo().fY - pSource->GetInfo().fY;

	// ��Ÿ���	
	float d = sqrtf(w * w + h * h);	

	return d <= fSumRad;
}
