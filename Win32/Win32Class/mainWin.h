#pragma once
#include "baseWin.h"

class MainWindow :public BaseWindow<MainWindow> {

public:
	virtual LPCWSTR ClassName() const;
	virtual LRESULT HandleMessage(UINT, WPARAM, LPARAM);

};