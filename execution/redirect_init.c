/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/06 17:20:02 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_redirection(t_parse *cmds_list, t_env *env_list,
		char **env_copy, t_data *data)
{
	(void)cmds_list;
	(void)env_list;
	(void)env_copy;
	(void)data;
	printf("Check redirection\n");
	int pipe_fd[2];
	int fork_id;
	if (pipe(pipe_fd) == -1)
		printf("Could not open pipe\n");
	fork_id = fork();

	if (fork_id == -1)
		printf("Could not fork\n");
	else if (fork_id == 0)
	{
		// it is child process
		if (cmds_list->infile_name)
		{
			int in_fd = open(cmds_list->infile_name, O_RDONLY);
			if (in_fd == -1)
				printf("File do not exist %d \n", in_fd);
			else
			{
				printf("file exist %d\n", in_fd); //
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				exec_shell(cmds_list, env_copy);
			}
		}
		close(pipe_fd[1]);
	}
	else
	{
		// parent process second fork
		int out_fd = open(cmds_list->outfile_name, O_RDONLY | O_CREAT);
		if (out_fd == -1)
			printf("Having problem with outfile %d\n", out_fd);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		exec_shell(cmds_list, env_copy);
	}
}