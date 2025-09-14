/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larmogid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:58:58 by larmogid          #+#    #+#             */
/*   Updated: 2022/10/18 11:34:40 by larmogid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <limits.h>
//#include <stdlib.h>

static char	ft_putnbr(int nb)
{
	unsigned int	number;

	number = nb;
	if (number == 0)
		return (0 + '0');
	if (number > 0)
	{
		ft_putnbr(number / 10);
		number %= 10;
	}
	return (number + '0');
}

static int	is_neg(int nb)
{
	if (nb < 0)
		return (1);
	return (0);
}

static size_t	get_len(int n)
{
	size_t			len;
	unsigned int	number;

	len = 0;
	if (is_neg(n))
	{
		number = (unsigned int)-n;
		len++;
	}
	else
		number = (unsigned int)n;
	while (number > 9)
	{
		number /= 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char			*result;
	size_t			len;
	unsigned int	num;
	int				i;

	len = get_len(n);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	if (is_neg(n))
		num = (unsigned int)-n;
	else
		num = (unsigned int)n;
	while (i++ <= (int)len - 1)
	{
		result[(int)len - i] = ft_putnbr(num);
		num /= 10;
	}
	if (is_neg(n))
		result[0] = '-';
	result[len] = '\0';
	return (result);
}
/*int	main(void)
{
	int	d;

	d = INT_MIN;
	printf("%d =? %s\n", d, ft_itoa(d));
	d = -13;
	printf("%d =? %s\n", d, ft_itoa(d));
	d = 0;
	printf("%d =? %s\n", d, ft_itoa(d));
	d = 5;
	printf("%d =? %s\n", d, ft_itoa(d));
	d = INT_MAX;
	printf("%d =? %s\n", d, ft_itoa(d));
}*/
