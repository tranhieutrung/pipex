/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:27:25 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 11:14:00 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_putbase_fd(int fd, unsigned long nb, char *base)
{
	unsigned int	len;
	unsigned int	baselen;
	int				check;

	len = 0;
	check = 0;
	baselen = ft_strlen(base);
	if (nb >= baselen)
	{
		check = ft_putbase_fd(fd, nb / baselen, base);
		if (check == -1)
			return (-1);
		else
			len += check;
	}
	if (ft_putchar_fd(fd, *(base + (nb % baselen))) == -1)
		return (-1);
	return (++len);
}
