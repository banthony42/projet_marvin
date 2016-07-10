#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	nb;
	char			*d;

	if (!s1 || !s2)
		return (NULL);
	nb = strlen(s1) + strlen(s2);
	if (!(str = (char *)malloc(sizeof(char) * nb + 1)))
		return (NULL);
	d = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str++ = '\0';
	return (str - (str - d));
}

char	*ft_strrev(char *str)
{
	int		length;
	int		nbr;
	int		middle;
	char	swap;

	length = 0;
	if (str)
		length = strlen(str);
	if (length == 0)
		return (NULL);
	middle = length / 2;
	nbr = 0;
	while (length > middle)
	{
		swap = *(str + nbr);
		*(str + nbr) = *(str + length - 1);
		*(str + length - 1) = swap;
		nbr++;
		length--;
	}
	return (str);
}

static char	*ft_itoan(int n, char *tmp, int i)
{
	++i;
	if (n <= -10)
		ft_itoan(n / 10, tmp, i);
	tmp[i] = '0' - n % 10;
	return (tmp);
}

static char	*ft_itoap(int n, char *tmp, int i)
{
	++i;
	if (n >= 10)
		ft_itoap(n / 10, tmp, i);
	tmp[i] = '0' + n % 10;
	return (tmp);
}

char		*ft_itoa(int n)
{
	char *number;
	char tmp[11];

	bzero(tmp, 11);
	number = NULL;
	if (n < 0)
		number = ft_strjoin("-", ft_strrev(ft_itoan(n, tmp, -1)));
	else
		number = strdup(ft_strrev(ft_itoap(n, tmp, -1)));
	return (number);
}
