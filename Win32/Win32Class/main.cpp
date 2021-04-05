#include "mainWin.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	MainWindow win;

	if (!win.Create(L"Win32 UI", WS_OVERLAPPEDWINDOW)) return -1;

	ShowWindow(win.Window(), nCmdShow);
	UpdateWindow(win.Window());

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}