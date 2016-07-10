#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

/*
 * Fonction print memory : Affiche toute la memoire de la taille demande
 */

static void	ft_put_hex(unsigned char nbr)
{
	if (nbr > 15)
		ft_put_hex(nbr / 16);
	if (nbr % 16 < 10)
		putchar('0' + nbr % 16);
	else if (nbr % 16 < 16)
		putchar('W' + nbr % 16);
}

static void	ft_affiche_hexa(unsigned char nbr)
{
	if (nbr < 16)
		putchar('0');
	ft_put_hex(nbr);

}

static void	ft_remize_a_zero(char *tab)
{
	int i = 0;

	while (i < 17)
		tab[i++] = 0;

}
	//oublie pas les flags
void	print_memory(const void *addr, size_t size)
{
	size_t nbr = 0;
	unsigned char *input = (unsigned char *)addr;
	char tab[17] = {0};

	if (!addr || size == 0)
		return ;

	while (nbr < size)
	{
		ft_affiche_hexa(*(input + nbr));

		if (isprint(*(input + nbr)))
			tab[nbr % 16] = *(input + nbr);
		else
			tab[nbr % 16] = '.';
		if (nbr % 2)
			putchar(' ');

		if (nbr % 16 == 15)
		{
			printf("%s",tab);
			ft_remize_a_zero(tab);
			putchar('\n');
		}
		++nbr;
	}
	if (nbr % 16)
	{
		while (nbr % 16)
		{
			putchar(' ');
			putchar(' ');
			if (nbr % 2)
				putchar(' ');
			if (nbr % 16 == 15)
			{
				printf("%s", tab);
				ft_remize_a_zero(tab);
				putchar('\n');
			}
			++nbr;
		}
	}
}
