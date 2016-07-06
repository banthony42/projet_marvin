#include "marvin.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>


void	marvin_add_ordre(t_marvin *marvin, char send)
{
	t_uart *new;	
	t_uart *tmp;

	if (!(new = new_elem(new)))
		return ;

	if (send == SEND)
		memccpy((void *)new->ordre, (void *)marvin->send, '\n', BUFF_SIZE);
	else
		memccpy((void *)new->ordre, (void *)marvin->receive, '\n', BUFF_SIZE);

	//print_memory(new->ordre, sizeof(marvin->send));
	if (send == SEND)
		clear_buffer(marvin->send);
	else
		clear_buffer(marvin->receive);
	//bzero(marvin->send, BUFF_SIZE);
	//
	//
	//
	//attention a faire sur r_begin

	if (send == SEND)
		tmp = marvin->s_begin;
	else
		tmp = marvin->r_begin;
	if (!tmp && send == SEND)
		marvin->s_begin = new;
	else if (!tmp && send == RECEIVE)
		marvin->r_begin = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (IS_DEBUG(marvin->options))
	{
		if (send == SEND)
			marvin_print_list(marvin->s_begin);
		else
		{
			printf("ordre en attente\n");
			marvin_print_list(marvin->r_begin);
		}
	}
}
