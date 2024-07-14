/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_triptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:40 by hitran            #+#    #+#             */
/*   Updated: 2024/07/14 15:04:27 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	ft_free_triptr(char ***strptr)
{
	if (*strptr)
	{
		while (**strptr)
			free(**strptr++);
		free(*strptr);
		*strptr = NULL;
	}
}
