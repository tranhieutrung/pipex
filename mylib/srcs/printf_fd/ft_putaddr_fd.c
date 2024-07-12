/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:59:56 by hitran            #+#    #+#             */
/*   Updated: 2024/07/12 21:59:58 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_putaddr_fd(int fd, void *ptr)
{
	int	len;

	if (!ptr)
		return (ft_putstr_fd(fd, "0x0"));
	len = ft_putstr_fd(fd, "0x");
	if (len == -1)
		return (-1);
	len += ft_putbase_fd(fd, (unsigned long)ptr, "0123456789abcdef");
	return (len);
}
