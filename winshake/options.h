#pragma once

#include <windows.h>

typedef struct Options
{
	int pixels;
	int step;
	int delay;
	BOOL showHelp;
} Options;

BOOL ParseArguments(int argc, char*argv[], Options* options);