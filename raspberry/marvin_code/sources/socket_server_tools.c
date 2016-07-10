#include "server.h"
#include "client.h"
#include "marvin.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
 * Recupere dans le buffer le resultat du client
 */

int		read_client(SOCKET sock, char *buffer)
{
	int n =0;
	if ((n = recv(sock, buffer, BUF_SIZE_SOCKET -1, MSG_DONTWAIT)) < 0)
	{
//		perror ("recv()");
		n = 0;
	}
	buffer[n] = 0;
	return n ;
}

/*
 * set and clear
 */

void	set_and_clear(t_marvin *marvin, fd_set *rdfs)
{
	int i = 0;
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	FD_ZERO(rdfs);

	/* add STDIN_FILENO */
	FD_SET(STDIN_FILENO, rdfs);

	/* add the connection socket */
	FD_SET(marvin->sock, rdfs);

	/* add socket of each client */
	for(i = 0; i < marvin->actual; i++)
	{
		FD_SET(marvin->clients[i].sock, rdfs);
	}

	if(select(marvin->max + 1, rdfs, NULL, NULL, &tv) == -1)
	{
		perror("select()");
		exit(errno);
	}
}

int	new_client(t_marvin *marvin, fd_set *rdfs)
{
	if(FD_ISSET(marvin->sock, rdfs))
	{
		/* new client */
		SOCKADDR_IN csin = { 0 };
		size_t sinsize = sizeof csin;
		int csock = accept(marvin->sock, (SOCKADDR *)&csin, &sinsize);
		if(csock == SOCKET_ERROR)
		{
			perror("accept()");
			return (1);	
		}

		/* after connecting the client sends its name */
		if(read_client(csock, marvin->buf_socket) == -1)
		{
			/* disconnected */
			return (1);
		}

		/* what is the new maximum fd ? */
		marvin->max = csock > marvin->max ? csock : marvin->max;

		FD_SET(csock, rdfs);

		Client c = { csock };
		strncpy(c.name, marvin->buf_socket, BUF_SIZE_SOCKET - 1);
		marvin->clients[marvin->actual] = c;
		marvin->actual++;
		return 1;
	}
	return 0;
}

/*
 * Init Connection
 */

int	init_connection(void)
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM , 0);
	SOCKADDR_IN sin = { 0 };

	if (sock == INVALID_SOCKET)
	{
		perror("exit socket\n");
		exit(errno);
	}

	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(PORT);
	sin.sin_family = AF_INET;

	if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
	{
		perror("bind()");
		exit(errno);
	}

	if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
	{
		perror("listen()");
		exit(errno);
	}

	return sock;
}

/*
 * end de la connexion
 */

void end_connection(int sock)
{
	closesocket(sock);
}

/*
 * Clear tous les clients
 */
void	clear_clients(Client *clients, int actual)
{
	int i = 0;
	for (i = 0; i < actual; i++)
	{
		closesocket(clients[i].sock);
	}

}


/*
 * Supprime le client 
 */

void	remove_client(Client *clients, int to_remove, int *actual)
{
	memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
	(*actual)--;
}

/*
 * envoie un message au client
 */

void	write_client(SOCKET sock, const char *buffer)
{
	printf("caca\n");
	if (send(sock, buffer, strlen(buffer), 0) < 0)
	{
		perror(("send"));
		exit(errno);
	}
}
// On sen bal les cacahuetes du sender car on vas envoyer a tous le monde ( 1 programme)
//void	send_message_to_all_clients(Clients *clients, Client sender, int actual, const char *buffer, char from_server)
/*
 * envoie un message a tous les clients
 */
void	send_message_to_all_clients(Client *clients, int actual, const char *buffer)
{
	int i = 0;
	//char message[BUF_SIZE_SOCKET]
	//message[0] = 0;

	// Bon on a un client donc la boucle est a la limite usell mais au cas ou si on ajoute d'autre programmes
	for (i = 0; i < actual; i++)
	{
		write_client(clients[i].sock, buffer);	
	}
}
