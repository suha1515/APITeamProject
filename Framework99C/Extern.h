#pragma once

#ifndef __EXTERN_H__

// extern Ű����: �ܺο� �̷��� ���������� �������� �˷��ִ� Ű����.
extern HWND g_hWnd;
extern HDC	g_hDC;
extern HINSTANCE g_hInst;
extern HBITMAP g_hBitmap;

extern float g_fDeltaTime;
extern float g_fElapsedTime;
extern float g_fTimeScale;
extern float g_fTotalTime;

// Ű����
extern const DWORD KEY_UP;
extern const DWORD KEY_DOWN;
extern const DWORD KEY_LEFT;
extern const DWORD KEY_RIGHT;

extern const DWORD KEY_ACTION;
extern const DWORD KEY_SPECIAL;

#define __EXTERN_H__
#endif
