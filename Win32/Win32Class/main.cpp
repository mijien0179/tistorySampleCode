#include "mainWin.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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