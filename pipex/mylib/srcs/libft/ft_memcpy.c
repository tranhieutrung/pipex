/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:37:56 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:42:27 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*dst_pt;

	dst_pt = dst;
	if (!dst && !src)
		return (dst);
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (dst_pt);
}
