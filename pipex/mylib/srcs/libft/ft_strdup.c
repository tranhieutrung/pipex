/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:52:52 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:43:03 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	char	*dest_pt;

	dest = (char *)malloc(ft_strlen(s1) + 1);
	if (dest == NULL)
		return (NULL);
	dest_pt = dest;
	while (*s1)
		*dest++ = *s1++;
	*dest = '\0';
	return (dest_pt);
}
