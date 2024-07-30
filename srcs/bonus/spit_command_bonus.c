/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spit_command_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:24 by hitran            #+#    #+#             */
/*   Updated: 2024/07/30 21:55:47 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	locate_quote(char *command, int i)
{
	if (command[i] == '\'')
	{
		i++;
		while (command[i] != '\'')
			i++;
	}
	else if (command[i] == '\"')
	{
		i++;
		while (command[i] != '\"')
			i++;
	}
	return (i);
}

static int	is_quote(char *command, int i)
{
	char	quote;

	quote = command[i];
	if (quote == '\'' || quote == '\"')
	{
		while (command[++i])
			if (command[i] == quote)
				return (1);
	}
	return (0);
}

static int	count_words(char *command)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] != 32)
		{
			words++;
			if (is_quote(command, i))
				i += locate_quote(command, i);
			while (command[i] && command[i] != 32)
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	**split_word(char *command, char **array, int words)
{
	int	i;
	int	j;

	i = 0;
	while (i < words)
	{
		while (*command == 32)
			command++;
		j = 0;
		if ((command[j] == '\'' || command[j] == '\"') && is_quote(command, j))
			j += locate_quote(command, j);
		while (command[j] && command[j] != 32)
			j++;
		array[i] = ft_substr(command, 0, j);
		if (!array[i])
		{
			ft_free_triptr(&array);
			return (NULL);
		}
		command += j;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**split_command(char *command)
{
	int		i;
	int		words;
	char	**array;
	char	*trimmed_command;

	if (!command)
		return (NULL);
	trimmed_command = ft_strtrim(command, " ");
	if (!trimmed_command)
		exit(1);
	if (*trimmed_command == 32 || !*trimmed_command)
		handle_empty_command(trimmed_command, command);
	words = count_words(trimmed_command);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split_word(trimmed_command, array, words);
	free (trimmed_command);
	i = -1;
	while (array && array[++i])
	{
		if ((*array[i] == '\'' || *array[i] == '\"') && is_quote(array[i], 0))
			array[i] = ft_substr(array[i], 1, ft_strlen(array[i]) - 2);
	}
	return (array);
}
