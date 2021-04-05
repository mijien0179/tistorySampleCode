/* https://pang2h.tistory.com/342 */
#include <Windows.h>
#include <cmath>

LRESULT OnPaint(HWND hwnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	for (int i = 1; i <= 800 / 50; ++i) {
		MoveToEx(hdc, i * 50 - 1, 0, nullptr);
		LineTo(hdc, i * 50 - 1, 500);
	}

	for (int i = 1; i <= 500 / 50; ++i) {
		MoveToEx(hdc, 0, i * 50, nullptr);
		LineTo(hdc, 800, i * 50);
	}

	return EndPaint(hwnd, &ps);
}

typedef struct _ITEM {
	POINT pos;
	bool isNext;
}ITEM;

ITEM password[5] = {
	{50, 50},
	{100, 100},
	{150, 150},
	{200, 200},
	{250, 250}
};

bool isDetect(POINT p1, POINT p2, double range = 20.0) {
	double result;
	result = pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2);

	if (result < pow(range, 2)) return true;
	return false;
}

LRESULT OnLButtonDown(POINT pos) {
	for (int i = 0; i < 5; ++i) {
		if (password[i].isNext) continue;

		if (isDetect(password[i].pos, pos)) {
			password[i].isNext = true;
			break;

		}
		else {
			for (int k = 0; k < i; ++k) {
				password[i].isNext = false;
			}
			break;
		}
	}

	bool isCorrect = true;
	for (int i = 0; i < 5; ++i) {
		isCorrect = password[i].isNext;
		if (!isCorrect) break;
	}

	if (isCorrect) {
		for (int i = 0; i < 5; ++i) password[i].isNext = false;
		MessageBox(nullptr, L"Correct", L"Login", MB_OK);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE: {
				PostQuitMessage(0);
				return 0;
			}

		case WM_DESTROY: {
				DestroyWindow(hwnd);
				return 0;
			}
	}

	switch (uMsg) {
		case WM_PAINT:
			{
				return OnPaint(hwnd);
			}
		case WM_LBUTTONDOWN:
			{
				POINT temp;
				temp.x = LOWORD(lParam);
				temp.y = HIWORD(lParam);
				return OnLButtonDown(temp);
			}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, int nCmdShow) {
	WNDCLASS wc{};

	wc.lpfnWndProc = WindowProc;
	wc.lpszClassName = L"Hello world";
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(L"Hello world", L"My First Win32 Program", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) return -1;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
