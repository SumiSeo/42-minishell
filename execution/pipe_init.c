/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 17:35:20 by sumseo           ###   ########.fr       */
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

void	execute_pipeline(char **argv, char *path, char **env)
{
	int i = 0;

	(void)path;
	int total_pipe = count_arr_length(argv);

	while (argv[i])
	{
		printf("PARSED PASSED ARGS %s\n", argv[i]);
		create_pipe(argv[i], env, total_pipe, i);
		i++;
	}
}