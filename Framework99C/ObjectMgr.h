#pragma once
//���� ���� ������Ʈ�� �����ϴ� ������

// ������ ���� (�޵����� ����)
// M : N  ���� ��ȣ ���⼺�� M : 1 �� ���ߴ� ������ ����
// ��� ������Ʈ���� ���θ� ���� �����ڸ� �˸� ��ȣ �ۿ� ó�� ����

class CGameObject;
class CObjectMgr
{
	DECLARE_SINGLE_TONE(CObjectMgr)
public:
	CGameObject* GetPlayer() const;
	const OBJLIST& GetObjectList(OBJECT_TYPE eType);

public:
	void AddObject(OBJECT_TYPE eType, CGameObject* pObject);
	void Update();
	void Render(HDC hDC);

private:
	void Release();
	void Initialize();
private:
	OBJLIST m_ObjLst[OBJECT_END];
};

