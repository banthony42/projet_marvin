#include "marvin.h"
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

void	read_input(t_marvin *marvin)
{
	int ret;
	size_t size;
	char *str;

	str = marvin->send;
	size = strlen(str);
	while (*str)
		++str;
	ret = read(0, str, BUFF_SIZE - size - 1);
	if (ret ==  -1)
		return ;
	if (strlen(str) + size > 250)
	{
		printf("Ordre trop long\n");
		bzero(marvin->send, BUFF_SIZE);
		return ;
	}
	if (ret)
	{
		if (*(str + ret - 1) == '\n')
		{
			marvin_add_ordre(marvin, SEND);
		}
	}
}

void send_data(t_marvin *marvin)
{
	int ret;

	 if (marvin->s_begin)
	 {
		 write(marvin->fd_uart, marvin->s_begin->ordre, strlen(marvin->s_begin->ordre));
		 marvin_destruct_ordre(marvin);
	 }
}	
