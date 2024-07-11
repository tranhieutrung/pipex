/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 11:06:16 by hitran            #+#    #+#             */
/*   Updated: 2024/07/11 11:12:11 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

static int	ft_conversion_fd(int fd, va_list args, char c)
{
	if (c == 'c')
		return (ft_putchar_fd(fd, va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_fd(fd, va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putaddr_fd(fd, va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(fd, va_arg(args, int)));
	else if (c == 'u')
		return (ft_putuint_fd(fd, va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthexa_fd(fd, va_arg(args, unsigned int), c));
	else if (c == '%')
		return (ft_putchar_fd(fd, '%'));
	else
		return (-1);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list			args;
	unsigned int	len;
	int				temp;

	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && ft_strchr("cspdiuxX%", *(str + 1)))
			temp = ft_conversion_fd(fd, args, *(str++ + 1));
		else
			temp = ft_putchar_fd(fd, *str);
		if (temp == -1)
			return (-1);
		len += temp;
		str++;
	}
	va_end(args);
	return (len);
}
