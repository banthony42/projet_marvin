#include <stdio.h>
#include "marvin.h"
#include <unistd.h>
#include <sys/wait.h>

void	marvin_left(t_marvin *marvin)
{
	char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "I'm turning left", NULL}; 
	if (IS_DEBUG(marvin->options))
	{
		printf("Ordre left \n");
	//	 espeak -ven+f3 -k5 -s150 "I've just picked up a fault in the AE35 unit"
	}
		execve("/usr/bin/espeak", test, NULL);
}

void	marvin_right(t_marvin *marvin)
{
	char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "I'm turning right", NULL}; 
	if (IS_DEBUG(marvin->options))
		printf("Ordre right\n");
	execve("/usr/bin/espeak", test, NULL);
}

void	marvin_sleep(t_marvin *marvin)
{
	char *test[] ={ "espeak", "-ven+m3", "-k20", "-s90", "I'm sleepy", NULL}; 
	if (IS_DEBUG(marvin->options))
		printf("Ordre sleep\n");
	execve("/usr/bin/espeak", test, NULL);
}


void	marvin_awake(t_marvin *marvin)
{

	char *test[] ={ "espeak", "-ven+f3", "-k5", "-s90", "Oh i wished always sleep", NULL}; 
	if (IS_DEBUG(marvin->options))
		printf("Ordre awake\n");
	execve("/usr/bin/espeak", test, NULL);

}

void	marvin_launch_order(t_marvin *marvin, int ordre)
{
	pid_t pid;
	int stat_loc;

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
		marvin->ordre[ordre].f(marvin);
	}
}
