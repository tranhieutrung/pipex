/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:37:08 by hitran            #+#    #+#             */
/*   Updated: 2024/08/03 22:56:14 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char *command)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == 39)
		{
			words++;
			i = skip_quotes(command, i);
		}
		else if (command[i] != 32)
		{
			words++;
			i = skip_word(command, i);
		}
		else
			i++;
	}
	return (words);
}

static char	*extract_word(char *command, int len)
{
	char	*word;
	int		i;
	int		j;

	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (command[i] == 39)
			i++;
		if (command[0] != 39 && command[i] == 32)
			i++;
		if (command[0] != 39 && command[i] == '\\' && command[i + 1] != '\0')
			i++;
		word[j++] = command[i++];
	}
	word[j] = '\0';
	return (word);
}

static char	**split_word(char *command, char **array, int words)
{
	int	i;
	int	j;

	j = -1;
	while (++j < words)
	{
		while (*command == 32)
			command++;
		i = 0;
		if (*command == 39)
			while (command[++i] != 39)
				;
		else
			i = skip_word(command, 0);
		array[j] = extract_word(command, i);
		if (!array[j])
		{
			ft_free_triptr(&array);
			return (NULL);
		}
		if (*command == 39)
			i++;
		command += i;
	}
	return (array);
}

char	**split_command(char *command)
{
	int		words;
	char	**array;

	if (!command)
		return (NULL);
	if (ft_is_all_white_spaces(command))
	{
		ft_printf_fd(2, "pipex: \"%s\": command not found\n", command);
		exit (127);
	}
	words = count_words(command);
	array = (char **)ft_calloc((words + 1), sizeof(char *));
	if (!array)
		return (NULL);
	array = split_word(command, array, words);
	return (array);
}
