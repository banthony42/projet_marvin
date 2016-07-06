#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "marvin.h"

int	main(int argc, char **argv)
{

	t_marvin marvin;


	printf("Lancement du Programme...\n");
	marvin_init(&marvin);
	marvin_options(&marvin, argc, argv);

	if (IS_DEBUG(marvin.options))
		printf("verbose mode\n");
	if (marvin.options == OPTION_ERROR)
	{
		printf("Invalid Arguments\n");
		printf("EXIT\n");
		return (-1);
	}
	marvin_init_uart(&marvin);
	while (1)
	{
		read_input(&marvin);	
		send_data(&marvin);
		receive_message(&marvin);
		if (marvin.nbrordres_receives >= MAX_ORDRE)
		{
			if (IS_DEBUG(marvin.options))
				printf("%d ordres ont ete recus\n", MAX_ORDRE);
			int ordre = 0;
			
			ordre = marvin_tri_ordre(marvin.r_begin, &marvin);
			if (ordre == 0)
			{
				if (IS_DEBUG(marvin.options))
					printf ("Aucun ordre valable\n");
			}
			else
			{
					if (IS_DEBUG(marvin.options))
						printf("L'ordre numero %d a ete recu \n", ordre);
					marvin_launch_order(&marvin, ordre);
			}
			//receive_message(&marvin);
			//clear uart
			char empty[2048];
			while (read(marvin.fd_uart, empty, 2047) > 0);
			marvin_destruct_receive(marvin.r_begin);
			marvin.nbrordres_receives = 0;
			marvin.r_begin = NULL;
			bzero(marvin.tab, sizeof(marvin.tab));
			bzero(marvin.receive, sizeof(marvin.receive));
			bzero(marvin.send, sizeof(marvin.send));
		}
	}
	return (0);
}
