/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/09 20:45:11 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execution(t_parse *cmds_list, char **env_copy, t_pipe *pipe_info)
{
	printf("Check execute pipe function\n");
	(void)cmds_list;
	(void)env_copy;
	(void)pipe_info;
	if (pipe_info)
	{
		printf("Pipe infile %d\n", pipe_info->infile);
		printf("Pipe outfile %d\n", pipe_info->outfile);
		printf("Pipe fd[0] %d\n", pipe_info->pipefd[0]);
		printf("Pipe fd[1] %d\n", pipe_info->pipefd[1]);
		return ;
	}
}

int	init_pipe(t_pipe *pipe_info)
{
	int	pipe_id;

	pipe_id = pipe(pipe_info->pipefd);
	if (pipe_id == -1)
	{
		printf("Pipe creatioin failed");
		return (0);
	}
	else
		return (1);
}
void	execute_pipeline(t_parse *cmds_list, char **env_copy)
{
	t_pipe *pipe_info;

	printf("Pipe execution started\n");
	pipe_info = (t_pipe *)malloc(sizeof(t_pipe));
	if (pipe_info == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	int total_count = count_cmds(cmds_list);
	int i = 0;
	while (i < total_count)
	{
		if (init_pipe(pipe_info))
		{
			int fork_id = fork();
			if (fork_id == -1)
				printf("Fork creatino failed\n");
			if (fork_id == 0)
			{
				redirection(cmds_list, pipe_info);
				printf("between redirectio and execution\n");
				execution(cmds_list, env_copy, pipe_info);
			}
			// else
			// 	wait(NULL);
		}
		i++;
	}
}