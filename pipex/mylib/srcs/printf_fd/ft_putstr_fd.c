/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd(int fd, .c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 23:07:47 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:44:13 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_putstr_fd(int fd, const char *s)
{
	if (!s)
		return (write(fd, "(null)", 6));
	if (write(fd, s, ft_strlen(s)) == -1)
		return (-1);
	return (ft_strlen(s));
}
