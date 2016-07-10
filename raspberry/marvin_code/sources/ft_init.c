#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include "marvin.h"


/*
 * Init des ordres
 */

static void	marvin_init_ordre(t_marvin *marvin)
{
	marvin->ordre[0].f = NULL;
	marvin->ordre[1].f = marvin_left;
	marvin->ordre[2].f = marvin_right;
	marvin->ordre[3].f = marvin_sleep;
	marvin->ordre[4].f = marvin_awake;
	marvin->ordre[5].f = marvin_camera;
}
/*
 * Init la struct t_marvin
 */

void	marvin_init(t_marvin *marvin)
{
	bzero(marvin->send, BUFF_SIZE);
	bzero(marvin->receive, BUFF_SIZE);
	bzero(marvin->buf_socket, BUF_SIZE_SOCKET);
	marvin->actual = 0;
	marvin->max = 0;
	marvin->s_begin = (void *)0;
	marvin->r_begin = (void *)0;
	marvin->options = 0;
	marvin->fd_uart = -1;
	marvin->nbrordres_receives = 0;
	marvin->last_ordre = 0;
	marvin_init_ordre(marvin);
	bzero(marvin->tab, sizeof(marvin->tab));
	marvin->speak = 0;
}

/*
 * Creation d'un maillon
 */

t_uart *new_elem(t_uart *new)
{
	if (!(new = (t_uart *)malloc(sizeof(t_uart))))
		return NULL;
	bzero(new->ordre, BUFF_SIZE);
	new->next = NULL;
	return (new);
}
/*
 * Creation de la nouvelle struct termios
 * Ouverture du fd pour l'uart
 */

void	marvin_init_uart(t_marvin *marvin)
{
	//Open in non blocking read/write mode
	

	int	 flag;
	marvin->fd_uart = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
	if (marvin->fd_uart == -1)
	{
		printf("Error init UART\n");
		exit(0);
	}
	struct termios options;
	tcgetattr(marvin->fd_uart, &options);
	options.c_cflag = B9600 | CS8 | CREAD;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(marvin->fd_uart, TCIFLUSH);
	tcsetattr(marvin->fd_uart, TCSANOW, &options);


	flag= fcntl(0, F_GETFL, 0);
	system("stty -icanon min 1");
	if (fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK) == -1)
	{
		printf("Error mode non bloquant\n");
		exit(0);
	}
	flag= fcntl(0, F_GETFL, 0);
	printf("Une p'tite attente\n");
	sleep(3);
	printf("UART configurer\n");
}
