/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:42:51 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:42:30 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*org_dst;

	org_dst = dst;
	if ((!dst && !src) || (dst == src))
		return (dst);
	if (dst < src)
		while (len--)
			*(char *)dst++ = *(char *)src++;
	else if (dst > src)
		while (len--)
			((char *)dst)[len] = ((char *)src)[len];
	return (org_dst);
}
