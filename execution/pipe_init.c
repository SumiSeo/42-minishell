/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/08 21:42:46 by sumseo           ###   ########.fr       */
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
void	create_pipe(t_parse *cmds_list, char **env_copy, t_data *data,
		t_pipe *cur_pipe)
{
	int	fork_id;

	printf("Check create pipe function\n");
	(void)cmds_list;
	(void)env_copy;
	(void)data;
	if (pipe(cur_pipe->pipefd) == -1)
		printf("There is a probem with pipe creation\n");
	fork_id = fork();
	if (fork_id == -1)
		printf("There is a probem with fork creation\n");
	if (fork_id == 0)
	{
		// check if there is < or << in the cmds list
		if (find_redirection(cmds_list))
			cur_pipe->fdi = 1;
		// if it exists open the file
		printf("Cure %d\n", cur_pipe->fdi);
		if (cur_pipe->fdi == 1)
		{
			open_infile(cmds_list, cur_pipe);
			printf("Here I am for opetning %d\n", cur_pipe->infile);
		}
		// if it does not exist take entree standard
		else
			take_standard_input(cmds_list, cur_pipe);
		// and then from here pipe two things
	}
	else
	{
		printf("I am parent process\n");
		wait(NULL);
	}
}

int	count_cmds(t_parse *cmds_list)
{
	int	total_cmd;

	total_cmd = 0;
	while (cmds_list)
	{
		if (cmds_list->cmd_array)
			total_cmd++;
		cmds_list = cmds_list->next;
	}
	return (total_cmd);
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
void	execute_pipeline(t_parse *cmds_list, t_env *env_list, char **env_copy,
		t_data *data)
{
	t_pipe *cur_pipe;
	(void)data;
	(void)env_list;
	(void)env_copy;

	printf("Pipe execution started\n");
	cur_pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (cur_pipe == NULL)
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
				// child process
				redirection(cmds_list);
				printf("Checkchcchhch\n");
			}
			else
				wait(0);
		}
		i++;
	}
}