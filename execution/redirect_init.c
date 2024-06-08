/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/07 21:08:55 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_redirection(t_parse *cmds_list, char **env_copy)
{
	int	pipe_fd[2];
	int	fork_id;
	int	in_fd;
	int	out_fd;

	if (pipe(pipe_fd) == -1)
		printf("Could not open pipe\n");
	fork_id = fork();
	if (fork_id == -1)
		printf("Could not fork\n");
	if (fork_id == 0)
	{
		in_fd = open(cmds_list->infile_name, O_RDONLY);
		if (in_fd == -1)
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			exec_shell(cmds_list, env_copy);
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			exec_shell(cmds_list, env_copy);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (fork() == 0)
		{
			close(pipe_fd[1]);
			// parent process second fork
			out_fd = open(cmds_list->outfile_name, O_WRONLY | O_TRUNC | O_CREAT,
					0644);
			if (out_fd == -1)
			{
				printf("Having problem with outfile %d\n", out_fd);
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				exec_shell(cmds_list, env_copy);
				exit(EXIT_FAILURE);
			}
			else
			{
				dup2(pipe_fd[0], STDIN_FILENO);
				close(pipe_fd[0]);
				dup2(out_fd, STDOUT_FILENO);
				close(out_fd);
				exec_shell(cmds_list, env_copy);
				exit(EXIT_FAILURE);
			};
			// close(pipe_fd[0]);
			// exit(EXIT_FAILURE);
		}
		else
		{
			close(pipe_fd[0]);
			wait(0);
		}
		wait(NULL);
	}
}
