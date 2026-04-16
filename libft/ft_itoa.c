/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leilai <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:00:00 by leilai            #+#    #+#             */
/*   Updated: 2025/10/29 18:01:46 by leilai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long nbr);

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*result;

	nbr = n;
	len = ft_intlen(nbr);
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		result[0] = '0';
	while (nbr != 0)
	{
		result[len - 1] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (result);
}

static int	ft_intlen(long nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

/*int	count_len(long n);

char	*ft_itoa(int nb)
{
	char	*res;
	int		count;
	int		i;
	long	n;

	n = nb;
	count = count_len(n);
	i = 0;
	if (n < 0 || count == 0)
		count++;
	if (!(res = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	res[count] = '\0';
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
		i++;
	}
	while (count > i)
	{	
		res[count - 1] = (n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (res);
}

int	count_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
	
#include <stdio.h>
int	main(void)
{
	int	n = -57427;
	printf("%d\n", ft_intlen(n));
	printf("%s\n", ft_itoa(n));
}
*/