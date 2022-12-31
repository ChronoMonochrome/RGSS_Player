#include <windows.h>
#include <sysinfoapi.h>
#include <stdio.h>

HINSTANCE hInst;

typedef int f_RGSSSetupRTP(WCHAR (*)[264], char (*)[2048], int);
typedef void f_RGSSInitialize2(HINSTANCE);

f_RGSSSetupRTP RGSSSetupRTP;

void initApplication(HINSTANCE hInstance)
{
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
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	hInst = hInstance;

	initApplication(hInst);
	
	DWORD TickCount = GetTickCount();

	while (GetTickCount() - TickCount < 500)
	{
		PeekMessage(&msg, NULL, 0, 0, 0);
		if (!GetMessage(&msg, 0, 0, 0))
			return 0;
		DispatchMessage(&msg);
	}
	
	WCHAR FileName[264];
	char v53[2048];
	HINSTANCE hrgss = LoadLibrary("E:\\dev\\cpp\\winapi\\helloworld\\RGSS202E.dll");
	if (!hrgss) {
		printf("could not load the dynamic library\n");
		//return EXIT_FAILURE;
	}
	
  // resolve function address here
   /*void *myptr = reinterpret_cast<void*>(GetProcAddress(hrgss, "RGSSSetupRTP"));
  f_RGSSSetupRTP RGSSSetupRTP = reinterpret_cast<f_RGSSSetupRTP> (myptr);
  if (!RGSSSetupRTP) {
    printf("could not locate the function RGSSSetupRTP\n");
    return EXIT_FAILURE;
  }
  
  int ret = RGSSSetupRTP(&FileName, &v53, 1024);
    if (!ret) {
		printf("RGSSSetupRTP failed with code %d\n", ret);
		return EXIT_FAILURE;
	}

*/
	printf("ok\n");
	while (true)
	{
		PeekMessage(&msg, NULL, 0, 0, 0);
		if (!GetMessage(&msg, 0, 0, 0))
			return 0;
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
