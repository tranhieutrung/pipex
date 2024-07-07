/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:42:14 by hitran            #+#    #+#             */
/*   Updated: 2024/06/07 09:43:37 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*trim;
	char			*trim_pt;
	unsigned int	start;
	unsigned int	end;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trim = (char *)malloc(end - start + 1);
	if (!trim)
		return (0);
	trim_pt = trim;
	while (*(s1 + start) && start < end)
		*trim++ = *(s1 + start++);
	*trim = '\0';
	return (trim_pt);
}
