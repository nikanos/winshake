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
		MoveWindow(hwnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);//we restore to saved position
	}
	return TRUE;
}

BOOL ParseInt(const char* str, int* pNum)
{
	if (str == NULL)
		return FALSE;

	char* endPtr;
	long result = strtol(str, &endPtr, 10);
	if (str == endPtr)
		return FALSE;

	if (result<INT_MIN || result>INT_MAX)
		return FALSE;

	if (pNum != NULL)
		*pNum = (int)result;
	return TRUE;
}