/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:56:32 by hitran            #+#    #+#             */
/*   Updated: 2024/08/03 22:53:20 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int *pipe_id)
{
	if (pipe(pipe_id) == -1)
	{
		perror("pipex: pipe\n");
		exit (1);
	}
}

void	redirect_fds(int from_fd1, int to_fd1, int from_fd2, int to_fd2)
{
	if (dup2(from_fd1, to_fd1) == -1 || dup2(from_fd2, to_fd2) == -1)
	{
		perror("pipex: dup2");
		close(from_fd1);
		close(from_fd2);
		exit(1);
	}
	close(from_fd1);
	close(from_fd2);
}

void	check_quote(int argc, char **argv)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		count = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'')
				count++;
			j++;
		}
		if (count % 2)
		{
			ft_printf_fd(2, "pipex: %s: unmatched single quote\n", argv[i]);
			exit (1);
		}
	}
}

int	skip_quotes(char *command, int i)
{
	i++;
	while (command[i] && command[i] != 39)
		i++;
	if (command[i] == 39)
		i++;
	return (i);
}

int	skip_word(char *command, int i)
{
	while (command[i] && command[i] != 32 && command[i] != 39)
	{
		if (command[i] == '\\' && command[i + 1] != '\0')
			i += 2;
		else
			i++;
	}
	return (i);
}
