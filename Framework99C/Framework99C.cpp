// Framework99C.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Framework99C.h"
#include "Maingame.h"

#define MAX_LOADSTRING 100

// ���� ����:
HWND g_hWnd;
// ���� ���۸��� ���� ����
HDC	g_hDC;
HBITMAP g_hBitmap;

// �����Ӱ� ���ݰ��� ����
float g_fDeltaTime;
float g_fElapsedTime;
float g_fTimeScale = 1.f;
// FPS ���� ����
TCHAR g_strFPS[10];
int g_nFPS;

HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.	

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAMEWORK99C, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }   

    MSG msg;
	msg.message = WM_NULL;

	CMaingame mainGame;
	mainGame.Initialize();

	// GetTickCount�Լ�: �ü��(OS)�� ���۵� �ڷ� �帥 �ð��� ������ ���� ��ȯ. 1/1000��
	DWORD dwOldTime = GetTickCount();
	DWORD dwCurTime = 0;

    // �⺻ �޽��� �����Դϴ�.
	while (WM_QUIT != msg.message)	
	{	
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // �޽��� ���� �Լ�.
			DispatchMessage(&msg);	// �޽��� ó���Լ�(WndProc)���� �޽����� ���� ����.
		}

		dwCurTime = GetTickCount();

		if (dwCurTime - dwOldTime >= 10) // 0.01�� �������� ����.
		{
			g_fDeltaTime = (int(dwCurTime - dwOldTime)) / 1000.f; // GetTickCount�� 1000�����̹Ƿ� 1000���� ���� ��
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
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   RECT rc = { 0, 0, WINCX, WINCY };

   // ���� Ŭ���̾�Ʈ ������ ũ�⸦ �����ϴ� �Լ�.
   // ���ϴ� Ŭ���̾�Ʈ ũ�⸦ RECT�� ��� �����ϸ�
   // ������ Ŭ���̾�Ʈ ũ�Ⱑ �ݿ��� ��ü ������ ũ�⸦ RECT�� ��ȯ�Ѵ�.
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
    case WM_DESTROY:	// �����찡 �ı��� �� �߻��ϴ� �޽���		
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}