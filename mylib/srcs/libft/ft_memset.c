/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:48:16 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:42:34 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*b_pt;

	b_pt = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (b_pt);
}
