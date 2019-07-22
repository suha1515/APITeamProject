// Framework99C.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Framework99C.h"
#include "Maingame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HWND g_hWnd;
// 더블 버퍼링을 위한 변수
HDC	g_hDC;
HBITMAP g_hBitmap;

// 프레임간 간격관련 변수
float g_fDeltaTime;
float g_fElapsedTime;
float g_fTimeScale = 1.f;
// FPS 관련 변수
TCHAR g_strFPS[10];
int g_nFPS;

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.	

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAMEWORK99C, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }   

    MSG msg;
	msg.message = WM_NULL;

	CMaingame mainGame;
	mainGame.Initialize();

	// GetTickCount함수: 운영체제(OS)가 시작된 뒤로 흐른 시각을 누적한 값을 반환. 1/1000초
	DWORD dwOldTime = GetTickCount();
	DWORD dwCurTime = 0;

    // 기본 메시지 루프입니다.
	while (WM_QUIT != msg.message)	
	{	
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // 메시지 번역 함수.
			DispatchMessage(&msg);	// 메시지 처리함수(WndProc)에게 메시지를 전달 역할.
		}

		dwCurTime = GetTickCount();

		if (dwCurTime - dwOldTime >= 10) // 0.01초 간격으로 진행.
		{
			g_fDeltaTime = (int(dwCurTime - dwOldTime)) / 1000.f; // GetTickCount가 1000단위이므로 1000으로 나눠 줌
			g_fElapsedTime += g_fDeltaTime;

			mainGame.Update();
			mainGame.Render();

			dwOldTime = dwCurTime;

			++g_nFPS;
		}

		TextOut(g_hDC, 50, 50, g_strFPS, lstrlen(g_strFPS));

		if (1.f <= g_fElapsedTime)
		{
			g_fElapsedTime -= 1.f;
			swprintf_s(g_strFPS, _T("%d"), g_nFPS);
			g_nFPS = 0;
		}
		
	}	

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAMEWORK99C));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rc = { 0, 0, WINCX, WINCY };

   // 순수 클라이언트 영역의 크기를 조정하는 함수.
   // 원하는 클라이언트 크기를 RECT에 담고 전달하면
   // 전달한 클라이언트 크기가 반영된 전체 윈도우 크기를 RECT에 반환한다.
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass, L"Hello world", WS_OVERLAPPEDWINDOW,
	   WINCX / 2, 0, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);

  g_hDC = CreateCompatibleDC(GetDC(hWnd));
  g_hBitmap = CreateCompatibleBitmap(GetDC(hWnd),WINCX,WINCY);
  SelectObject(g_hDC, g_hBitmap);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   DeleteObject(g_hBitmap);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {	
	case WM_KEYDOWN:
		switch (wParam)
		{		
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;       
    case WM_DESTROY:	// 윈도우가 파괴될 때 발생하는 메시지		
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}