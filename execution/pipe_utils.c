/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:29:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/24 20:00:30 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_pipeline(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	create_first_pipe(char *cmd, char **env)
{
	int	pid;
	int	pipe_fd[2];
	int	fd_in;

	(void)env;
	if (pipe(pipe_fd) == -1)
		exit_program("Pipe creation failed");
	else
	{
		pid = fork();
		if (pid == 0)
		{
			close(pipe_fd[0]);
			// [p[0] for read]
			// [p[1] for write]
			// down cmd should be replaced with filename or sortie
			fd_in = open(cmd, O_RDONLY);
			if (fd_in == -1)
				exit_program("File can not be opened");
			else
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			close(pipe_fd[1]);
		}
		else
			wait(0);
	}
}

void	create_last_pipe(char *cmd, char **env)
{
	(void)cmd;
	(void)env;
	printf("****created last pipe\n");
}