/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/23 23:56:13 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(char *cmd, char **env, int total, int i)
{
	int	id;
	int	pipe_fd[2];

	(void)env;
	(void)cmd;
	if (i == 0)
		create_first_pipe(cmd, env);
	else if (i + 1 == total)
		create_last_pipe(cmd, env);
	else
	{
		if (pipe(pipe_fd) == -1)
			perror("ERROR:");
		id = fork();
		if (id == 0)
		{
			// child element
		}
		else
		{
			// close(pipe_fd[1]);
			// create_second_fork(pipe_fd, path, env);
			wait(0);
		}
	}
}

void	create_pipeline(char **argv, char *path, char **env)
{
	int i = 0;

	(void)path;
	int total_pipe = count_pipeline(argv);

	while (argv[i])
	{
		printf("PARSED PASSED ARGS %s\n", argv[i]);
		create_pipe(argv[i], env, total_pipe, i);
		i++;
	}
}