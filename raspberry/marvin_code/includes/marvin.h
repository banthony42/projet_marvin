#ifndef MARVIN_H
#define MARVIN_H

#include <sys/types.h>

/* Size du Buffer send de l'uart*/
#define BUFF_SIZE 255


/* Options debuf */
#define OPTION_ERROR -1
#define OPTION_DEBUG 1
//#define IS_DEBUG(x) {return (x & -1 == -1 ? 0 : x & 1 == 1 ? printf("vrai : %d\n", x) : printf("false : %d\n", x))} 
//#define IS_DEBUG(x) (x & -1 == -1 ? 0 : x & 1 == 1 ? 1 : 0) 
#define IS_DEBUG(x) (x & 1) == 1 ? (x == -1 ? 0 : 1) : 0

#define SEND 1
#define RECEIVE 2


#define MAX_ORDRE 5 // le nombre d'ordre a recevoir avant de faire un traitement
// l'ordre zero est une erreur car atoi renvoi zero en cas d'erreur
#define NBR_ORDRES 6 // Les ordres sont sur des entiers attention ca commence a zero qui l'erreur

/* liste chaine des ordres recus pas le PIC */
typedef struct s_uart
{
	char 					ordre[BUFF_SIZE];
	struct	s_uart  *next;

}				t_uart;

typedef struct s_marvin t_marvin;
/* tableau de pointeur sur fonctions */
typedef struct s_ordre
{
	void	(*f)(t_marvin *);		
}				t_ordre;

#include "server.h"
struct s_marvin 
{
	char			send[BUFF_SIZE];
	char			receive[BUFF_SIZE];
	t_uart	*s_begin;//liste chaine des ordres a envoyer	
	t_uart	*r_begin;//liste chaine des	informations recus 
	int			options;
	int			fd_uart;
	int			tab[NBR_ORDRES];
	t_ordre		ordre[NBR_ORDRES];
	int 		nbrordres_receives;
	int			last_ordre;
	char		buf_socket[BUF_SIZE_SOCKET];
	int			actual; // les clients
	int			max;
	SOCKET		sock;
	Client clients[MAX_CLIENTS];
	int			speak;
}				;


/*********************************
 * 			INIT
 ***********************************/

void	marvin_init();
void	marvin_init_uart(t_marvin *);
t_uart	*new_elem(t_uart *);

/*********************************
 *          LIST
 *******************************/

void	marvin_add_ordre(t_marvin *, char);

/********************************
 * 			Destruct
 ********************************/

void	marvin_destruct_ordre(t_marvin *);
void	clear_buffer(char *str);
void	marvin_destruct_receive(t_uart *);
/******************************
 * 			UART
 ******************************/

void	send_data(t_marvin *);
void	read_input(t_marvin *);
void	receive_message(t_marvin *);

/***************************
 * 			ORDRE
 ****************************/

int		marvin_tri_ordre(t_uart *, t_marvin *);
void	marvin_left();
void	marvin_right();
void	marvin_sleep();
void	marvin_awake();
void	marvin_camera();
void	marvin_launch_order(t_marvin *, int);

/****************************
 * 			DEBUG
 ****************************/
void	print_memory(const void *, size_t);
void	marvin_print_list(t_uart *);
void	marvin_options(t_marvin *, int, char **);
#endif
