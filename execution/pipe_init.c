/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/09 19:53:39 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_redirection(t_parse *cmds_list)
{
	if (cmds_list->infile_exist)
		return (1);
	return (0);
}

int	open_infile(t_parse *cmds_list, t_pipe *cur_pipe)
{
	cur_pipe->infile = open(cmds_list->infile_name, O_RDONLY);
	if (cur_pipe->infile == -1)
		return (0);
	return (1);
}

int	take_standard_input(t_parse *cmds_list, t_pipe *cur_pipe)
{
	(void)cmds_list;
	(void)cur_pipe;
	printf("This file doex not exists\n");
	return (0);
}
void	execution(t_parse *cmds_list, char **env_copy, t_pipe *pipe_info)
{
	(void)pipe_info;
	printf("Check execute pipe function\n");
	(void)cmds_list;
	(void)env_copy;
}

int	init_pipe(void)
{
	int	fd[2];
	int	pipe_id;

	pipe_id = pipe(fd);
	if (pipe_id == -1)
	{
		printf("Pipe creatioin failed");
		return (0);
	}
	else
		return (1);
}
void	execute_pipeline(t_parse *cmds_list, char **env_copy, t_data *data)
{
	t_pipe *pipe_info;
	(void)data;

	printf("Pipe execution started\n");
	pipe_info = (t_pipe *)malloc(sizeof(t_pipe));
	if (pipe_info == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	int total_count = count_cmds(cmds_list);
	printf("Total cmds count check %d\n", total_count);
	int i = 0;
	while (i < total_count)
	{
		if (init_pipe())
		{
			int fork_id = fork();
			if (fork_id == -1)
				printf("Fork creatino failed\n");
			if (fork_id == 0)
			{
				redirection(cmds_list, pipe_info);
				execution(cmds_list, env_copy, pipe_info);
			}
			else
				wait(NULL);
		}
		i++;
	}
}