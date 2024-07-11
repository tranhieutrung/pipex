/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:14:54 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:42:44 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static void	putnbr(long nb, int fd)
{
	if (nb / 10 > 0)
		putnbr(nb / 10, fd);
	ft_putchar_fd((nb % 10 + '0'), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	putnbr(nb, fd);
}
