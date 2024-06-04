/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/04 18:04:32 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(char *cmd, char **env, int total, int i)
{
	int	id;
	int	pipe_fd[2];

	if (i == 0)
		create_first_pipe(cmd, env);
	else if (i + 1 == total)
		create_last_pipe(cmd, env);
	else
	{
		if (pipe(pipe_fd) == -1)
			exit_program("Pipe creation failed");
		id = fork();
		if (id == 0)
		{
			// child element
			printf("I am child process\n");
		}
		else
		{
			// close(pipe_fd[1]);
			// create_second_fork(pipe_fd, path, env);
			wait(0);
		}
	}
}

void	execute_pipeline(t_parse *cmds_list, t_env *env_list, char **env_copy,
		t_data *data)
{
	(void)cmds_list;
	(void)env_list;
	(void)env_copy;
	(void)data;
}