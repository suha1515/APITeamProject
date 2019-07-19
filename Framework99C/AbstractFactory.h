#pragma once

// ������ ����

// �߻� ���丮 ����
// ������Ʈ�� ������ �� ����� ��Ҹ� ��Ƽ� ĸ��ȭ�� ������ ����.
class CGameObject;

template <typename T>
class CAbstractFactory
{
public:
	static CGameObject* CreateObject()
	{
		CGameObject* pInstance = new T;
		pInstance->Initialize();

		return pInstance;
	}

	static CGameObject* CreateObject(float x, float y)
	{
		CGameObject* pInstance = new T;
		pInstance->Initialize();
		pInstance->SetPos(x, y);

		return pInstance;
	}
};