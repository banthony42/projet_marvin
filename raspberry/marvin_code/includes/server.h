#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#define CRLF "\n\r"
#define PORT 1977
#define MAX_CLIENTS 10
#define BUF_SIZE_SOCKET 1024

#include "client.h"
#include "marvin.h"

//typedef struct s_marvin t_marvin;
void clear_clients(Client *client, int actual);
void remove_client(Client *clients, int to_remove, int *actual);
void send_message_to_all_clients(Client *, int, const char *);
int	 init_connection();
void	end_connection(int);
void	write_client(SOCKET sock, const char * buffer);
int	read_clients(SOCKET, char *);
void	set_and_clear(t_marvin *marvin,  fd_set *);
int		new_client(t_marvin *, fd_set *);
int		read_client(SOCKET, char *);
#endif
