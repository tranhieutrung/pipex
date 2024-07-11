/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:11:16 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:43:27 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*(unsigned char *)s1 == *(unsigned char *)s2
		&& *(unsigned char *)s1 && --n)
	{
		s1++;
		s2++;
	}
	if (*(unsigned char *)s1 == *(unsigned char *)s2)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
