/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// Programming Windows 3.1
/// Page 17-18
/// 
/// HELLOWIN.C を Visual Studio 2022でコンパイルできるように書き換え
/// 
/// 主な変更点
///		UNICODE対応
///		WndProcの呼び出し
///		WinMainの呼び出し
/// 
///	
///   履歴	
///   2023/09/18 V1.00 First
///
///
///                        Copyright(c) 2023, Retar.jp, All Rights Reserved.
///                        http://www.retar.jp/
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// マルチバイト
/// 構成プロパティ　－＞　詳細　－＞　文字セット　－＞　マルチ バイト文字セットを使用する
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
HELLOWIN.C - Displays "Hello, Windows!" in client area(c)
             Charles Petzold, 1992
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "HellowWin.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//long FAR PASCAL _export WndProc(HWND, UINT, UINT, LONG); <- c言語のスタイルなので、現代のC++風にする
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) <- WinMainがオーバーロードされるように書き換え
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ PWSTR pCmdLine,
	_In_ int nCmdShow
)
{
	static char szAppName[] = "HelloWin";
	HWND hwnd;
	MSG msg;
	WNDCLASSA wndclass;																//WNDCLASSAで正しくロードされるようにする
	//
	if (!hPrevInstance)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = WndProc;												//正しくオーバーロードされるようにする
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIconA(hInstance, MAKEINTRESOURCEA(IDI_HELLOWWIN));		//LoadIconAで正しくロードされるようにする
		wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);							//リソースを読み込む
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = szAppName;
		//
		RegisterClassA(&wndclass);
	}
	//
	hwnd = CreateWindowA(															//CreateWindowAで正しくロードされるようにする
		szAppName,						// window class name
		"The Hello Program",			// window caption							//マルチバイト文字セットにしないと正しく表示されない
		WS_OVERLAPPEDWINDOW,			// window style
		CW_USEDEFAULT,					// initial x position
		CW_USEDEFAULT,					// initial y position
		CW_USEDEFAULT,					// initial x size
		CW_USEDEFAULT,					// initial y size 
		NULL,							// parent window handle
		NULL,							// window menu handle
		hInstance,						// program instance handle
		NULL);							// creation parameters
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//long FAR PASCAL _export WndProc(HWND hwnd, UINT message, UINT wParam, LONG IParam); <- WinMainがオーバーロードされるように書き換え
LRESULT CALLBACK  WndProc(
	HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	//
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawTextA(
			hdc,
			"Hello, Windows!",
			-1,
			&rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
