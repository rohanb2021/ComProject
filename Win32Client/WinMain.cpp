#include<Windows.h>
#include "win32client.h"

LRESULT CALLBACK WindowsProcedure(HWND, UINT, WPARAM, LPARAM);

TCHAR AppName[] = TEXT("ASTROMEDICOMP");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpzsCmdLine, int iCmdShow)
{
	//DialogBox(hInstance, TEXT("Record"), NULL, DialogProcdure);
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hInstance = hInstance;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc = WindowsProcedure;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName, AppName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return ((int)msg.wParam);
}




LRESULT CALLBACK WindowsProcedure(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hWndDc;
	HFONT hMyFont;
	PAINTSTRUCT ps;
	HGDIOBJ obj;
	static RECT rc;
	BITMAP bmBuffer;
	HDC hMemoryDC;
	static HBITMAP hBitmap;
	TCHAR str[] = TEXT("Press space to open recorder dialog !!!   ");
	HINSTANCE hInst;

	switch (iMsg)
	{
	case WM_CREATE:
		hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));
		break;
	case WM_PAINT:
		hWndDc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hMemoryDC = CreateCompatibleDC(NULL);  // brush 
		obj = SelectObject(hMemoryDC, hBitmap);  /// instruction to paint
		GetObject(hBitmap, sizeof(BITMAP), &bmBuffer);
		StretchBlt(hWndDc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemoryDC, 0, 0, bmBuffer.bmWidth, bmBuffer.bmHeight, SRCCOPY);
		// Send back the specilist & stop painting
		DeleteDC(hMemoryDC);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
