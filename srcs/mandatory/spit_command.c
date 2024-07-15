/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:24 by hitran            #+#    #+#             */
/*   Updated: 2024/07/15 23:31:47 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	ft_free_set_null(char **str)
{
	free(*str);
	*str = NULL;
}

void	ft_multiple_free_set_null(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i] != NULL)
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}

char	*ft_return_multiple_free_set_null(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i] != NULL)
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

void	ft_split_skip_delimiter(char const **s, char delimiter)
{
	while (**s && **s == delimiter)
		(*s)++;
}

const char	*ft_skip_quote(const char **s)
{
	char	quote;

	quote = **s;
	(*s)++;
	while (**s)
	{
		if (**s == quote)
		{
			(*s)++;
			return (*s);
		}
		else if (**s == '\\' && *(*s + 1))
		{
			(*s) += 2;
		}
		else
			(*s)++;
	}
	return (NULL);
}

void	*ft_memcpy_esc(void	*dst, void const *src, size_t n)
{
	void	*return_dst;

	return_dst = dst;
	if (!dst && !src)
		return (dst);
	while (n--)
	{
		if (*(char *)src == '\\')
			src++;
		*(char *)dst++ = *(char *)src++;
	}
	return (return_dst);
}

static size_t	ft_wordcount(const char *s, char delimiter)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		ft_split_skip_delimiter(&s, delimiter);
		if (*s)
		{
			count++;
			if (*s == '\'' || *s == '\"')
			{
				if (ft_skip_quote(&s) == NULL)
					break ;
			}
			else
			{
				while (*s && *s != delimiter && *s != '\'' && *s != '\"')
					s++;
			}
		}
	}
	return (count);
}

static void	ft_cal_word_quote(
	const char **s,
	const char **start,
	size_t *current_word_len,
	char quote
)
{
	int	esc_count;

	esc_count = 0;
	if (**s == '\'' || **s == '\"')
	{
		(*s)++;
		*start = *s;
		while (**s)
		{
			if (**s == '\\' && *(*s + 1))
			{
				esc_count++;
				(*s) += 2;
			}
			else if (**s == quote)
			{
				*current_word_len = *s - *start - esc_count;
				(*s)++;
				return ;
			}
			else
				(*s)++;
		}
	}
}

static void	ft_cal_word_alloc(
	const char **s,
	const char **start,
	char delimiter,
	size_t *current_word_len)
{
	*start = *s;
	*current_word_len = 0;
	if (**s == '\'' || **s == '\"')
	{
		ft_cal_word_quote(s, start, current_word_len, **s);
	}
	else
	{
		while (**s && **s != delimiter)
			(*s)++;
		*current_word_len = *s - *start;
	}
}

static char	**ft_split_helper(
	char **res,
	const char *s,
	char delimiter,
	size_t i
)
{
	size_t		current_word_len;
	const char	*start;

	while (*s)
	{
		ft_split_skip_delimiter(&s, delimiter);
		if (*s)
		{
			ft_cal_word_alloc(&s, &start, delimiter, &current_word_len);
			res[i] = (char *)malloc((current_word_len + 1) * sizeof(char));
			if (!res[i])
			{
				ft_multiple_free_set_null(&res);
				return (NULL);
			}
			ft_memcpy_esc(res[i], start, current_word_len);
			res[i][current_word_len] = '\0';
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
static inline void	ft_empty_cmd(char *trimmed_cmd, char *org_cmd)
{
	if (trimmed_cmd[0] == ' ' || !trimmed_cmd[0])
		ft_printf_fd(2, "%s: %s: command not found\n", "pipex", org_cmd);
	free(trimmed_cmd);
	exit (127);
}

char	**split_command(char *cmd, char delimiter)
{
	char	**res;
	size_t	size;
	char	*trimmed_cmd;

	trimmed_cmd = ft_strtrim(cmd, " ");
	if (!trimmed_cmd)
		exit(1);
	if (!*trimmed_cmd)
		ft_empty_cmd(trimmed_cmd, cmd);
	size = ft_wordcount(trimmed_cmd, delimiter);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
	{
		return (NULL);
	}
	res = ft_split_helper(res, trimmed_cmd, delimiter, 0);
	free(trimmed_cmd);
	return (res);
}*/

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

// #k su dung pipex