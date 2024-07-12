/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:24 by hitran            #+#    #+#             */
/*   Updated: 2024/07/12 22:14:23 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	count_words(char *command)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (command[i])
	{
		if (command[i] != ' ')
			words++;
		if ((command[i] == '\'' || command[i] == '\"')
			&& verify_quote(command, i))
			i += is_quote(command, i);
		while (command[i] && command[i] != ' ')
			command++;
		while (command[i] && command[i] == ' ')
			command++;
	}
	return (words);
}

static char	**final_split(char **final, char *command, int words)
{
	int	counter;
	int	i;

	counter = -1;
	while (++counter < words)
	{
		while (*command == ' ')
			command++;
		i = 0;
		if ((command[i] == '\'' || command[i] == '\"')
			&& verify_quote(command, i))
			i += is_quote(command, i);
		while (command[i] && command[i] != ' ')
			i++;
		final[counter] = ft_substr(command, 0, i);
		if (!final[counter])
			return (ft_free_strptr(final), NULL);
		command += i;
	}
	return (final[counter] = NULL, final);
}

char	**split_command(char *command)
{
	int		i;
	int		words;
	char	**array;
	char	**trim;

	if (!command)
		return (NULL);
	words = count_words(command);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = word_split(command, array, words);
	i = -1;
	while (trim[++i])
	{
		if ((trim[i][0] == '\'' || trim[i][0] == '\"')
			&& verify_quote(trim[i], 0))
			trim[i] = remove_quote(trim[i], trim[i][0]);
	}
	return (trim);
}
