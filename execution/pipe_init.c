/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/06 16:13:10 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(t_parse *cmds_list, t_env *env_list, char **env_copy,
		t_data *data)
{
	(void)cmds_list;
	(void)env_list;
	(void)env_copy;
	(void)data;
}

void	execute_pipeline(t_parse *cmds_list, t_env *env_list, char **env_copy,
		t_data *data)
{
	int pipe_fd[2];

	int fd_in;
	int fd_out;
	(void)cmds_list;
	(void)env_list;
	(void)env_copy;
	(void)data;

	printf("Pipe execution started\n");
	if (data->has_pipe < 1)
	{
		if (pipe(pipe_fd) == -1)
			printf("There is problem with pipe creation\n");
		if (fork() == -1)
			printf("There is problem with fork creation\n");
		else
		{
			fd_in = open(cmds_list->infile_name, O_RDONLY);
			if (fd_in == -1)
				printf("Error\n");

			else
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				fd_out = open(cmds_list->infile_name, O_RDONLY | O_CREAT);
				printf("Check file int fd_in %d\n", fd_in);
				// dup2(fd_in, STDIN_FILENO);
				// close(fd_in);
				// dup2(pipe_fd[1], STDOUT_FILENO);
			}

			// create antoher process
			// parent process
			// close(pipe_fd[0]);
			// dup2(pipe_fd[1], STDERR_FILENO);
			// close(pipe_fd[1]);
			// wait(NULL);
		}
	}
	else
	{
		create_pipe(cmds_list, env_list, env_copy, data);
	}
}