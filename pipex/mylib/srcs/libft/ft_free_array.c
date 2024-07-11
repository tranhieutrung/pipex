/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:09:09 by hitran            #+#    #+#             */
/*   Updated: 2024/07/05 12:39:50 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	ft_free_array(size_t size, char **array)
{
	if (array)
	{
		while (size-- > 0)
			if (*(array + size))
				free(*(array + size));
		free(array);
	}
}
