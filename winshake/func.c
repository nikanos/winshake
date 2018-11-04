#include "func.h"
#include "options.h"

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	Options* options = (Options*)lParam;
	if (IsWindowVisible(hwnd))
	{
		RECT rc;
		GetWindowRect(hwnd, &rc);
		for (int i = options->pixels; i >= 0; i -= options->step)
		{
			MoveWindow(hwnd, rc.left, rc.top + i, rc.right - rc.left, rc.bottom - rc.top, TRUE);
			MoveWindow(hwnd, rc.left, rc.top - i, rc.right - rc.left, rc.bottom - rc.top, TRUE);
			if (options->delay > 0)
				Sleep(options->delay);
		}
	}
	return TRUE;
}