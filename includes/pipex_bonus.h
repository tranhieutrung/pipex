/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:56 by hitran            #+#    #+#             */
/*   Updated: 2024/07/29 12:10:22 by hitran           ###   ########.fr       */
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
	int		fd[2];
	int		error;
}	t_pipex;

void	execute_pipex(t_pipex *pipex);
char	*find_command_path(char **envp, char **command);
char	**split_command(char *command);
void	print_and_exit(char *message, int error_number);
void	handle_error(char *message, int error_number, char **command);
void	handle_exec_error(char *command_path, char **splitted_command);
void	handle_empty_command(char *trimmed_command, char *command);
void 	handle_open_error(char *name, int pipe_num);
void 	handle_fork_error(int fd1, int fd2);

#endif