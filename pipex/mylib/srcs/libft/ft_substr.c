/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:13:21 by hitran            #+#    #+#             */
/*   Updated: 2024/07/03 18:49:05 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	char			*substr_pt;
	unsigned int	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	s += start;
	substr_pt = substr;
	*(substr + len) = '\0';
	while (*s && len--)
		*substr++ = *s++;
	return (substr_pt);
}
