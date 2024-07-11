/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:38:53 by hitran            #+#    #+#             */
/*   Updated: 2024/04/23 22:00:54 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*s_pt;

	s_pt = (char *)s;
	while (*s)
	{
		if (*(char *)s == (char)c)
			s_pt = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	if (*s_pt == (char)c)
		return (s_pt);
	return (0);
}
