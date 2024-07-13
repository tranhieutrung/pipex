/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:56 by hitran            #+#    #+#             */
/*   Updated: 2024/07/13 22:59:33 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "mylib.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		pipe[2];
	int		fd[2];
	pid_t	pid;
	int		error;
}	t_pipex;

void	execute_pipex(t_pipex *pipex);
char	*find_command_path(t_pipex *pipex, char **commands);
char	**split_command(char *command);
void	handle_error_126(char *command, char **splitted_command);
void	handle_error_127(char *command, char **splitted_command);
void	handle_error_exec(char *command_path, char **splitted_command);
void	handle_empty_command(char *trimmed_command, char *command);

#endif
