/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:54:51 by hitran            #+#    #+#             */
/*   Updated: 2024/07/07 23:55:50 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h> //WRITE, FORK, PIPE, EXECVE
# include <stdlib.h> //MALLOC, NULL
# include <fcntl.h> //OPEN, CLOSE
# include <sys/wait.h> //WAITPID
# include <stdio.h> //PERROR

typedef struct s_pipex
{
	pid_t	pid;
	int		pipe[2];
	int		fd[2];
	int		ac;
	char	*path;
	char	**cmdargs;
	char	**envi;
}	t_pipex;

//----------PIPEX----------//
void	cmd_controller(t_pipex *pipex, int cmds_size, char **cmds, int i);
char	**spliter(char *cmd);
char	*pathfinder(t_pipex *pipex);

//----------BONUS----------//
char	*get_next_line(int fd);

//----------CLEANER----------//
void	cleaner_matrix(char **matrix);

//----------QUOTE----------//
int		verify_quote(char *cmd, int i);
int		is_quote(char *cmd, int i);
char	*remove_quote(char *trim, char quote);

#endif //PIPEX_BONUS
