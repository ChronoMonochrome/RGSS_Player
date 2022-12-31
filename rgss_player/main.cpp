#include <windows.h>
#include <sysinfoapi.h>
#include <stdio.h>

#include <iostream>
#include <sstream>
#include <vector>
using std::vector;
using std::string;

HINSTANCE hInst;

typedef int (*f_RGSSSetupRTP)(WCHAR **, char **, int);
typedef void (*f_RGSSInitialize2)(HINSTANCE);
typedef void (*f_RGSSGameMain)(HWND hWnd, WCHAR*, WCHAR*);

f_RGSSSetupRTP RGSSSetupRTP;
f_RGSSInitialize2 RGSSInitialize2;
f_RGSSGameMain RGSSGameMain;

#define MSG(x) MessageBoxA(hwnd, x, "", MB_OKCANCEL)
#define MSGW(x) MessageBoxW(hwnd, x, L"", MB_OKCANCEL)

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	hInst = hInstance;

	WNDCLASS wC;

	wC.cbClsExtra = 0;
	wC.cbWndExtra = 0;
	wC.hbrBackground = NULL;
	wC.hInstance = hInst;
	wC.hCursor = LoadCursor(NULL, IDC_ARROW);
	wC.hIcon= LoadIcon(NULL, IDI_APPLICATION);
	wC.lpszClassName = "Main";
	wC.lpfnWndProc = DefWindowProcW;
	wC.lpszMenuName = NULL;
	wC.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wC);

	HWND hwnd = CreateWindow("Main", "Main", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, hInstance, 0);

	ShowWindow(hwnd, SW_SHOW);

	UpdateWindow(hwnd);
	
	DWORD TickCount = GetTickCount();

	while (GetTickCount() - TickCount < 500)
	{
		PeekMessage(&msg, NULL, 0, 0, 0);
		if (!GetMessage(&msg, 0, 0, 0))
			return 0;
		DispatchMessage(&msg);
	}

	WCHAR FileName[264];
	char FileNameA[2048];
	HINSTANCE hrgss = LoadLibraryA(".\\RGSS202E.dll");
	int ret;
	
	char ScriptsStr[50] = "Data\\Scripts.rvdata";
	WCHAR ScriptsStrW[100];

	char RgssFilenameStr[256] = "Game.rgss2a";
	WCHAR RgssFilenameStrW[512];

	std::mbstowcs(ScriptsStrW, ScriptsStr, strlen(ScriptsStr) + 1);
	std::mbstowcs(RgssFilenameStrW, RgssFilenameStr, strlen(RgssFilenameStr) + 1);

	if (!hrgss) {
		string s("could not load the dynamic library ");
		s += GetLastError();
		
		MSG(s.c_str());
		return EXIT_FAILURE;
	}

	RGSSSetupRTP = (f_RGSSSetupRTP)GetProcAddress(hrgss, "RGSSSetupRTP");
	if (!RGSSSetupRTP) {
		MSG("could not locate the function RGSSSetupRTP");
		goto out;
	}

	RGSSInitialize2 = (f_RGSSInitialize2)GetProcAddress(hrgss, "RGSSInitialize2");
	if (!RGSSInitialize2) {
		MSG("could not locate the function RGSSInitialize2");
		goto out;
	}

	RGSSGameMain = (f_RGSSGameMain)GetProcAddress(hrgss, "RGSSGameMain");
	if (!RGSSGameMain) {
		MSG("could not locate the function RGSSGameMain");
		goto out;
	}

	ret = RGSSSetupRTP(reinterpret_cast<WCHAR**>(&FileName), reinterpret_cast<char**>(&FileNameA), 1024);
	if (!ret) {
		string s("RGSSSetupRTP failed with code ");

		s += ret;

		MSG(s.c_str());
		goto out;
	}

	RGSSInitialize2(hrgss);
	RGSSGameMain(hwnd, ScriptsStrW, RgssFilenameStrW);
out:
	FreeLibrary(hrgss);

	return msg.wParam;
}