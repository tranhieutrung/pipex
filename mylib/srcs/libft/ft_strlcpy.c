/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:07:40 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:43:16 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	srcsize;

	srcsize = ft_strlen(src);
	if (dstsize < 1)
		return (srcsize);
	while (*src && --dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (srcsize);
}
