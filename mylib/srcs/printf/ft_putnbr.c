/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:14:54 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:44:09 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_putnbr(int n)
{
	long			nb;
	unsigned int	len;
	int				check;

	len = 0;
	check = 0;
	nb = (long)n;
	if (nb < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		else
			len = 1;
		nb *= -1;
	}
	check = ft_putbase(nb, "0123456789");
	if (check == -1)
		return (-1);
	else
		len += check;
	return (len);
}
