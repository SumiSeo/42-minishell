/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/11 21:51:24 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first_pipe_exec(t_parse *cmds_list, char **env_copy, t_pipe *pipe_info)
{
	// if (pipe_info->infile)
	// {
	pipe_info->temp = open("tmp", O_WRONLY | O_RDONLY);
	// close(pipe_info->pipefd[0]);
	dup2(pipe_info->infile, STDIN_FILENO);
	dup2(pipe_info->pipefd[1], STDOUT_FILENO);
	parse_path(cmds_list, env_copy);
	// }
}
void	execution(t_parse *cmds_list, char **env_copy, t_pipe *pipe_info)
{
	printf("Execution started\n");
	if (!cmds_list->prev)
	{
		printf("FIRST COMMAND: %s\n", cmds_list->cmd_array[0]);
		first_pipe_exec(cmds_list, env_copy, pipe_info);
		// dup2(pipe_info->infile, STDIN_FILENO);
		// dup2(pipe_info->temp, STDOUT_FILENO);
	}
	else if (!cmds_list->next)
	{
		printf("LAST COMMAND: %s\n", cmds_list->cmd_array[0]);
		dup2(pipe_info->pipefd[0], STDIN_FILENO);
		dup2(pipe_info->outfile, STDOUT_FILENO);
		parse_path(cmds_list, env_copy);
	}
	else
	{
		printf("MIDDLE COMMAND: %s\n", cmds_list->cmd_array[0]);
		dup2(pipe_info->pipefd[0], STDIN_FILENO);
		dup2(pipe_info->pipefd[1], STDOUT_FILENO);
		parse_path(cmds_list, env_copy);
	}
	// execute command and then pass it to the next pipe
}

int	init_pipe(t_pipe *pipe_info)
{
	int	pipe_id;

	pipe_id = pipe(pipe_info->pipefd);
	pipe_info->total_pipe++;
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

	pipe_info = (t_pipe *)malloc(sizeof(t_pipe));
	if (pipe_info == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	int total_count = count_cmds(cmds_list);
	int i = 0;

	int tmp_in = dup(STDIN_FILENO);
	int tmp_out = dup(STDOUT_FILENO);

	if (tmp_in == -1 || tmp_out == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}

	int fd_in;
	if (cmds_list->infile_exist)
	{
		fd_in = open(cmds_list->infile_name, O_RDONLY);
		if (fd_in == -1)
		{
			perror("open input file");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fd_in = dup(tmp_in);
		if (fd_in == -1)
		{
			perror("dup tmp_in");
			exit(EXIT_FAILURE);
		}
	}
	int fd_out;
	int fork_id;
	while (i < total_count)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);

		if (i == total_count - 1)
		{
			if (cmds_list->outfile_name && cmds_list->outfile_token)
			{
				fd_out = open(cmds_list->outfile_name,
						O_WRONLY | O_TRUNC | O_CREAT, 0644);
				if (fd_out == -1)
				{
					perror("open output file");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				fd_out = dup(tmp_out);
				if (fd_out == -1)
				{
					perror("dup tmp_out");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			int fdpipe[2];
			if (pipe(fdpipe) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			fd_out = fdpipe[1];
			fd_in = fdpipe[0];
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		fork_id = fork();
		if (fork_id == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (fork_id == 0)
		{
			parse_path(cmds_list, env_copy);
			perror("Execute error");
			exit(EXIT_FAILURE);
		}
		cmds_list = cmds_list->next;
		i++;
	}
	while (i < total_count)
	{
		if (wait(NULL) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
}