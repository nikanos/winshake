#include "options.h"
#include "func.h"
#include "getopt.h"

#define ARG_DEFAULT_SHOWHELP	FALSE
#define ARG_DEFAULT_DELAY		0
#define ARG_DEFAULT_PIXELS		10
#define ARG_DEFAULT_STEP		1

BOOL ParseArguments(int argc, char* argv[], Options* options)
{
	options->showHelp = ARG_DEFAULT_SHOWHELP;
	options->delay = ARG_DEFAULT_DELAY;
	options->pixels = ARG_DEFAULT_PIXELS;
	options->step = ARG_DEFAULT_STEP;

	int option;
	while ((option = getopt(argc, argv, "p:s:d:h")) != -1)
	{
		BOOL parseResult;
		int num;
		switch (option)
		{
		case 'p':
			parseResult = ParseInt(optarg, &num);
			if (!parseResult)
				return FALSE;
			options->pixels = num;
			break;
		case 's':
			parseResult = ParseInt(optarg, &num);
			if (!parseResult)
				return FALSE;
			options->step = num;
			break;
		case 'd':
			parseResult = ParseInt(optarg, &num);
			if (!parseResult)
				return FALSE;
			options->delay = num;
			break;
		case 'h':
			options->showHelp = TRUE;
			break;
		}
	}
	return TRUE;
}