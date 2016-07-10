#include "marvin.h"
#include <stdlib.h>

void	clear_buffer(char *str)
{
	char *d;

	d = str;
	while (*str != '\n')
		*str++ = '\0';
	*str++ = '\0';
	while (*str)
		*d++ = *str++;

}

void	marvin_destruct_ordre(t_marvin *marvin)
{
	t_uart *tmp;

	tmp = marvin->s_begin;
	marvin->s_begin = tmp->next;
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}


void	marvin_destruct_receive(t_uart *receive)
{
	if (receive && receive->next)
		marvin_destruct_receive(receive->next);
	if (receive)
	{
		receive->next = NULL;
		free(receive);
	}
}
