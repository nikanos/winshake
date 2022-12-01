#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include "func.h"

void ShowUsage();
void ShowError(const char* format, ...);
void vShowError(const char* format, va_list argp);

#define MUTEX_NAME "WINSHAKE_83D1ADA0A8B74A2AAE66F575D3AF8DB8"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	BOOL result;
	Options options;
	HANDLE hMutex;
	int returnValue;

	hMutex = CreateMutex(/*lpMutexAttributes*/ NULL, /*bInitialOwner*/ TRUE, /*lpName*/ MUTEX_NAME);
	if (hMutex == NULL)
	{
		ShowError("CreateMutex() error %d", GetLastError());
		return EXIT_FAILURE;
	}
	else
	{
		//CreateMutex returned a valid handle. Check whether it was initially created by another process.
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			ShowError("Application is already running");
			CloseHandle(hMutex);
			return EXIT_FAILURE;
		}
	}

	result = ParseArguments(__argc, __argv, &options);
	if (result)
	{
		if (options.showHelp)
			ShowUsage();
		else
			EnumWindows(EnumWindowsProc, (LPARAM)&options);
		returnValue = EXIT_SUCCESS;
	}
	else
	{
		ShowUsage();
		returnValue = EXIT_FAILURE;
	}

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return returnValue;
}

void ShowUsage()
{
	char message[1024];
	snprintf(message, sizeof(message), "-p <number of pixels>\n-s <pixels step>\n-d <delay in milliseconds>");
	MessageBox(NULL, message, "Usage", MB_OK);
}

void ShowError(const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	vShowError(format, argp);
	va_end(argp);
}

void vShowError(const char* format, va_list argp)
{
	char errorMessage[1024];
	snprintf(errorMessage, sizeof(errorMessage), format, argp);
	MessageBox(NULL, errorMessage, "Error", MB_OK | MB_ICONERROR);
}