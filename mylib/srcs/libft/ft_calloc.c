/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:40:10 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:41:29 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;
	size_t	total;

	total = count * size;
	if (count && size && total / count != size)
		return (NULL);
	dest = malloc(total);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, total);
	return (dest);
}
