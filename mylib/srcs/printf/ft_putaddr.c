/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:14:52 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:43:53 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_putaddr(void *ptr)
{
	int	len;

	if (!ptr)
		return (ft_putstr("0x0"));
	len = ft_putstr("0x");
	if (len == -1)
		return (-1);
	len += ft_putbase((unsigned long)ptr, "0123456789abcdef");
	return (len);
}
