/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:35:40 by hitran            #+#    #+#             */
/*   Updated: 2024/07/12 22:06:00 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

void	ft_free_strptr(char **strptr)
{
	if (strptr)
	{
		while (*strptr)
			free(*strptr++);
		free(strptr);
	}
}
