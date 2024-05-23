/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/23 23:33:41 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(char *cmd, char *path, char **env, int total)
{
	int	id;
	int	pipe_fd[2];

	(void)path;
	(void)env;
	(void)cmd;
	if (pipe(pipe_fd) == -1)
		perror("ERROR:");
	id = fork();
	// find first
	// control medium
	// find last
	if (id < 0)
	{
		// fork failed
	}
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

void	create_pipeline(char **argv, char *path, char **env)
{
	int i = 0;

	int total_pipe = count_pipeline(argv);
	printf("total pipe %d\n", total_pipe);

	// multiple commands handler
	while (argv[i])
	{
		printf("PARSED PASSED ARGS %s\n", argv[i]);
		create_pipe(argv[i], path, env, total_pipe);
		i++;
	}
}