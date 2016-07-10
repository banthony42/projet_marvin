#include "client.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc , char ** argv)
{
	if(argc < 2)
	{
		printf("Usage : %s [address] [pseudo]\n", argv[0]);
		return 1;
	}

	char buffer[BUF_SIZE_SOCKET];

	fd_set rdfs;
	//SOCKET define sur intd
	SOCKET sock = init_connection(argv[1]);

	/* send our name*/
	write_server(sock, argv[2]);


	while (1)
	{
		FD_ZERO(&rdfs); // Vide l'ensemble
		/*add STDION_FILENO */ //descripteur 0
		FD_SET(STDIN_FILENO, &rdfs);
		/* add socket*/
		FD_SET(sock, &rdfs);

		if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			perror("error select");
			exit(errno);
		}
		if (FD_ISSET(STDIN_FILENO, &rdfs))
		{
			fgets(buffer, BUF_SIZE_SOCKET - 1, stdin);
			{
				char *p = NULL;
				p = strstr(buffer, "\n");
				if (p != NULL)
				{
					*p = 0;
				}
				else
				{
					/* fclean */
					buffer[BUF_SIZE_SOCKET -1] = 0;
				}
			}
			write_server(sock, buffer);
		}
		else if(FD_ISSET(sock, &rdfs))
		{
			int n = read_server(sock, buffer);

			/*server down*/
			if (n == 0)
			{
				printf("Server disconnected !\n");
				break;
			}
			puts(buffer);
			write_server(sock, "ok");
		}
	}
	end_connection(sock);
	return (0);
}
