#pragma once
class CCollsionMgr
{
public:
	CCollsionMgr();
	~CCollsionMgr();

public:
	// �ܼ��浹�� AABB
	static bool CollisionRect(const OBJLIST& dstLst, const OBJLIST& srcLst);
	// �浹������ VECTOR�� ��ȯ�ϴ� AABB ���� 3��° ���ڿ� �ּҷ� �ѱ��ȴ�.
	static bool CollisionRectEX(const OBJLIST& dstLst, const OBJLIST& srcLst);
	static void CollisionSphere(const OBJLIST& dstLst, const OBJLIST& srcLst);

private:
	static bool CheckSphere(const CGameObject* pDest, const CGameObject* pSource);
};

