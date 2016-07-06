#include <stdio.h>
#include "marvin.h"
#include <unistd.h>
#include <string.h>


static void	fill_message(t_marvin *marvin)
{
	char *d;
	
	if (strchr(marvin->receive, '\n'))
	{
		marvin->nbrordres_receives++;
		marvin_add_ordre(marvin, RECEIVE);
	}
}

void	receive_message(t_marvin *marvin)
{
	int rx_length = 0;


	char *d;

	d = marvin->receive;
	while (*d)
		++d;

	while ((rx_length = read(marvin->fd_uart, d, BUFF_SIZE)) > 0)
	{
		if (IS_DEBUG(marvin->options))
		{
			printf("Octet recu %d\n", rx_length);
			print_memory(d, rx_length);
		}
		fill_message(marvin);
	}
}
