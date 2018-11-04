#include <windows.h>
#include <stdio.h>
#include "options.h"
#include "func.h"

void ShowUsage();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	BOOL result;
	Options options;
	result = ParseArguments(__argc, __argv, &options);
	if (result)
	{
		if (options.showHelp)
			ShowUsage();
		else
			EnumWindows(EnumWindowsProc, (LPARAM)&options);
		return 0;
	}
	else
	{
		ShowUsage();
		return -1;
	}
}

void ShowUsage()
{
	char message[1024];
	snprintf(message, sizeof(message), "-p <number of pixels>\n-s <pixels step>\n-d <delay in milliseconds>");
	MessageBox(NULL, message, "Usage", MB_OK);
}