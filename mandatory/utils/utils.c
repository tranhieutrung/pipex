
#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	while (*s && *s != ch)
		s++;
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	n -= 1;
	i = -1;
	while ((s1[++i] || s2[i]) && i < n)
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*final;

	final = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (final == NULL)
		return (NULL);
	i = -1;
	while (s[++i])
		final[i] = s[i];
	final[i] = '\0';
	return (final);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_size;
	char	*new_s;

	s_size = ft_strlen(s);
	if ((size_t)start > s_size)
		return (ft_strdup(""));
	s += start;
	s_size -= start;
	if (s_size > len)
		s_size = len;
	new_s = malloc(sizeof(char) * (s_size + 1));
	if (new_s == NULL)
		return (NULL);
	i = -1;
	while (++i < s_size)
		new_s[i] = s[i];
	new_s[i] = '\0';
	return (new_s);
}
