#include "stdafx.h"
#include "KeyboardMgr.h"

const DWORD KEY_UP = 0x00000001;
const DWORD KEY_DOWN = 0x00000002;
const DWORD KEY_LEFT = 0x00000004;
const DWORD KEY_RIGHT = 0x00000008;

const DWORD KEY_ACTION = 0x00000010;
const DWORD KEY_SPECIAL = 0x00000020;

const DWORD KEY_CHEAT = 0x00000040;

DEFINE_SINGLE_TONE(CKeyboardMgr)

void CKeyboardMgr::Initialize() 
{
	m_dwKey = 0;
	m_dwKeyDown = 0;
	m_dwKeyUp = 0;
}

void CKeyboardMgr::Update()
{
	m_dwKey = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwKey |= KEY_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwKey |= KEY_RIGHT;

	if (GetAsyncKeyState('A') & 0x8000)
		m_dwKey |= KEY_ACTION;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwKey |= KEY_SPECIAL;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwKey |= KEY_CHEAT;
		
}

bool CKeyboardMgr::KeyPressed(DWORD dwCurKey)
{
	if (m_dwKey & dwCurKey)
		return true;

	return false;
}

bool CKeyboardMgr::KeyDown(DWORD dwCurKey)
{
	if (!(m_dwKeyDown & dwCurKey) && (m_dwKey & dwCurKey))
	{
		m_dwKeyDown |= dwCurKey;
		return true;
	}

	if ((m_dwKeyDown & dwCurKey) && !(m_dwKey & dwCurKey))
	{
		m_dwKeyDown ^= dwCurKey;
		return false;
	}

	return false;
}

bool CKeyboardMgr::KeyUp(DWORD dwCurKey)
{
	if (!(m_dwKeyUp & dwCurKey) && (m_dwKey & dwCurKey))
	{
		m_dwKeyUp |= dwCurKey;
		return false;
	}

	if ((m_dwKeyUp & dwCurKey) && !(m_dwKey & dwCurKey))
	{
		m_dwKeyUp ^= dwCurKey;
		return true;
	}

	return false;
}
