
#include "pipex.h"

int	is_quote(char *cmd, int i)
{
	if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	else if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	return (i);
}

int	verify_quote(char *cmd, int i)
{
	char	quote;

	quote = cmd[i];
	while (cmd[++i])
		if (cmd[i] == quote)
			return (1);
	return (0);
}

char	*remove_quote(char *trim, char quote)
{
	size_t	trim_size;
	char	s_quote[1];
	char	*new;

	s_quote[0] = quote;
	while (*trim && ft_strchr(s_quote, *trim))
		trim++;
	trim_size = ft_strlen(trim) - 1;
	while (trim[trim_size] && ft_strchr(s_quote, trim[trim_size]))
		trim_size--;
	new = ft_substr(trim, 0, trim_size + 1);
	return (new);
}
