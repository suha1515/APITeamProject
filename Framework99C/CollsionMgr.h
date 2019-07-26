#pragma once
class CCollsionMgr
{
DECLARE_SINGLE_TONE(CCollsionMgr)

private:
	void Initialize();

public:
	// �ܼ��浹�� AABB
	bool CollisionRect(const OBJLIST& dstLst, const OBJLIST& srcLst);
	CGameObject* CollisionRectReturn(const CGameObject* pDst, OBJECT_TYPE type);
	// �浹������ VECTOR�� ��ȯ�ϴ� AABB ���� 3��° ���ڿ� �ּҷ� �ѱ��ȴ�.
	void CollisionSphere(const OBJLIST& dstLst, const OBJLIST& srcLst);

	bool CollisionRectEX(const OBJLIST& dstLst, const OBJLIST& srcLst);

private:
	bool CheckSphere(const CGameObject* pDest, const CGameObject* pSource);
};
