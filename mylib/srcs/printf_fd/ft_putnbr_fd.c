/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:59:44 by hitran            #+#    #+#             */
/*   Updated: 2024/07/12 21:59:45 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_putnbr_fd(int fd, int n)
{
	long			nb;
	unsigned int	len;
	int				check;

	len = 0;
	check = 0;
	nb = (long)n;
	if (nb < 0)
	{
		if (ft_putchar_fd(fd, '-') == -1)
			return (-1);
		else
			len = 1;
		nb *= -1;
	}
	check = ft_putbase_fd(fd, nb, "0123456789");
	if (check == -1)
		return (-1);
	else
		len += check;
	return (len);
}
