/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:39:37 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:42:23 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_pt;
	unsigned char	*s2_pt;

	s1_pt = (unsigned char *)s1;
	s2_pt = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (--n && *s1_pt == *s2_pt)
	{
		s1_pt++;
		s2_pt++;
	}
	if (*s1_pt == *s2_pt)
		return (0);
	else
		return (*s1_pt - *s2_pt);
}
