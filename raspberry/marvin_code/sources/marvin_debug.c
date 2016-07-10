#include "marvin.h"
#include <stdio.h>
#include <string.h>

static int marvin_add_options(t_marvin *marvin, char *str)
{
	if (!strcmp(str, "-e"))
		marvin->options |= OPTION_DEBUG;
	else
	{
		marvin->options = OPTION_ERROR;
		return (0);
	}
	return (1);
}

void	marvin_options(t_marvin *marvin, int argc, char **argv)
{
	while (argc > 1)
	{
		if (!(marvin_add_options(marvin, *(++argv))))
			break;
		--argc;
	}
}

void	marvin_print_list(t_uart *print)
{
	while (print)
	{
		//printf("%s\n", print->ordre);
		print_memory(print->ordre, sizeof(print->ordre));
		print = print->next; 
	}
}
