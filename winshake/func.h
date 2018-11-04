#pragma once

#include <windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
BOOL ParseInt(const char* str, int* pNum);