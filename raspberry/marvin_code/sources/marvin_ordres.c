#include <stdio.h>
#include "marvin.h"
#include <unistd.h>
#include <sys/wait.h>
#include "server.h"
#include "time.h"
#include <string.h>
#include <stdlib.h>

// a < b

static int rand_a_b(int a, int b){
	    return rand()%(b-a) +a;
}


void	marvin_left(t_marvin *marvin)
{
	if (IS_DEBUG(marvin->options))
	{
		printf("Ordre left \n");
		//	 espeak -ven+f3 -k5 -s150 "I've just picked up a fault in the AE35 unit"
	}
	if (marvin->speak % 2)
	{
		char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "-p10", "left", NULL}; 
		execve("/usr/bin/espeak", test, NULL);
	}
	else
	{
		char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "-p10", "freeze ? i'm a robot, not a refrigerator", NULL}; 
		execve("/usr/bin/espeak", test, NULL);
	}
}

void	marvin_right(t_marvin *marvin)
{
	if (IS_DEBUG(marvin->options))
		printf("Ordre right\n");
	if (marvin->speak % 2)
	{
		char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "-p10", "right", NULL}; 
		execve("/usr/bin/espeak", test, NULL);
	}
	else
	{
		char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "-p10", "freeze ? i'm a robot, not a refrigerator", NULL}; 
		execve("/usr/bin/espeak", test, NULL);
	}
}

void	marvin_sleep(t_marvin *marvin)
{
	char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "I think you ought to know i'm feeling very depress", NULL}; 
	if (IS_DEBUG(marvin->options))
		printf("Ordre sleep\n");
	execve("/usr/bin/espeak", test, NULL);
}


void	marvin_awake(t_marvin *marvin)
{

	char *test[] ={ "espeak", "-ven+f3", "-k5", "-s90", "life, don't talk to me about life?", NULL}; 
	if (IS_DEBUG(marvin->options))
		printf("Ordre awake\n");
	execve("/usr/bin/espeak", test, NULL);

}

void	marvin_camera(t_marvin *marvin)
{
	write_client(marvin->clients[0].sock, "start");	
	time_t t = time(0);
	int oui = 0;
	int stat_loc;
	pid_t pid;

	while (t + 5 > time (0))
	{
		if (read_client(marvin->clients[0].sock, marvin->buf_socket))
		{
			if (!strcmp("1", marvin->buf_socket))
			{
				if (IS_DEBUG(marvin->options))
					printf("oui\n");
				oui++;
			}
			else
			{
				if (IS_DEBUG(marvin->options))
					printf("non\n");
				oui--;
			}
			//	printf("%s\n", marvin->buf_socket);
		}
	}
	printf("fin de la transmition camera\n");
	write_client(marvin->clients[0].sock, "stop");
	if (oui > 0)
	{
		write(marvin->fd_uart, "1", 1);
		printf("Trouver\n");
	}
	else
	{
		write(marvin->fd_uart, "0", 1);
		printf("pas trouver\n");
	}
	pid = fork();
	if (pid < 0)
	{
		printf("Probleme sur les processus\n");
		return ;
	}
	if (pid != 0)
	{
		/* Processus Parent */
		waitpid(pid, &stat_loc, WUNTRACED);
	}
	else
	{
		if (oui > 0)
		{
			char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "-p10", "oh my god, you ugly as fuck", NULL}; 
			execve("/usr/bin/espeak", test, NULL);
		}
		else
		{
			char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "-p10", "I can't find you", NULL}; 
			execve("/usr/bin/espeak", test, NULL);
		}
	}

}
void	marvin_launch_order(t_marvin *marvin, int ordre)
{
	pid_t pid;
	int stat_loc;

	/* order de la camera*/
	marvin->speak = rand(); if (ordre == 5) { marvin->ordre[ordre].f(marvin); } else { pid = fork(); if (pid < 0) { printf("Probleme sur les processus\n");
			return ;
		}
		if (pid != 0)
		{
			/* Processus Parent */
			waitpid(pid, &stat_loc, WUNTRACED);
		}
		else
		{
			marvin->ordre[ordre].f(marvin);
		}
	}
}
