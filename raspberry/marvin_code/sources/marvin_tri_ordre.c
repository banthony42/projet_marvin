#include <stdlib.h>
#include <stdio.h>
#include "marvin.h"


static	int best_ordre(int *tab)
{
	int i;
	int best;
	int	nbr_ordre;

	best = 0;
	i = 0;
	nbr_ordre = 0;
	if (tab[3] > 0)
		return 3 ;
	if (tab[4] > 0)
		return 4 ;

	while (i < NBR_ORDRES)
	{
		printf("tab de i %d\n", tab[i]);
		if (tab[i] > nbr_ordre && tab[i] > NBR_ORDRES / 2)
		{
			best = i;
			nbr_ordre = tab[i];
		}
		++i;
	}
	printf("ordre retourner %d\n", best);
	return (best);

}
/*
 * Retourne l'ordre a effectuer en fonctions des nombres recus
 * Retourne -1 si aucun ordre n'est valable
 */

int 	marvin_tri_ordre(t_uart *receive, t_marvin *marvin)
{
	int ordre;

	while (receive)
	{
		ordre = atoi(receive->ordre);
		printf("Ordre recu %d\n", ordre);
		if (ordre >= 0 && ordre < NBR_ORDRES) 
			marvin->tab[ordre]++;	
		else
			marvin->tab[0]++;
		receive = receive->next;	
	}	
	return (best_ordre(marvin->tab));
}	
