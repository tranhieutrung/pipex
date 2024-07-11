/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:19:24 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:43:12 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	len;

	if ((!dst || !src) && !dstsize)
		return (0);
	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (dlen >= dstsize)
		return (dstsize + slen);
	len = dlen + slen;
	while (*src && dlen < dstsize - 1)
		*(dst + dlen++) = *src++;
	*(dst + dlen) = '\0';
	return (len);
}
