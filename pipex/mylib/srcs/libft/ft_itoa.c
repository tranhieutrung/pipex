/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:25:38 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:41:43 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static int	length(long nb)
{
	int	length;

	length = 0;
	if (nb < 1)
		length++;
	while (nb)
	{
		nb /= 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	nb = (long)n;
	i = length(nb);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (0);
	str[i] = '\0';
	if (nb < 0)
		nb *= -1;
	while (i--)
	{
		str[i] = 48 + (nb % 10);
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
