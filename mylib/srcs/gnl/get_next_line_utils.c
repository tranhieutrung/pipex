/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:37:59 by hitran            #+#    #+#             */
/*   Updated: 2024/07/03 18:49:05 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	*ft_free_gnl(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

int	ft_strlen_gnl(char *str)
{
	int	len;

	len = 0;
	if (str)
		while (str[len])
			++len;
	return (len);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		++s;
	}
	if ((*s == '\0') && (c == '\0'))
		return ((char *)s);
	return (NULL);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	char			*substr_pt;
	unsigned int	slen;

	if (!s)
		return (0);
	slen = ft_strlen_gnl((char *)s);
	if (start >= slen)
		len = 0;
	if (len > slen - start)
		len = slen - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	substr_pt = substr;
	*(substr + len) = '\0';
	while (s[start] && len--)
		*substr++ = s[start++];
	return (substr_pt);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	str = (char *)malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!str)
		return (ft_free_gnl(&s1));
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}
