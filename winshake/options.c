#include "options.h"
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
		switch (option)
		{
		case 'p':
			options->pixels = atoi(optarg);
			break;
		case 's':
			options->step = atoi(optarg);
			break;
		case 'd':
			options->delay = atoi(optarg);
			break;
		case 'h':
			options->showHelp = TRUE;
			break;
		}
	}
	return TRUE;
}