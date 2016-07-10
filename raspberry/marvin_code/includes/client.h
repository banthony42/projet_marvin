#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
typedef struct 
{
	SOCKET sock;
	char name[BUF_SIZE_SOCKET];
}Client;
#endif
