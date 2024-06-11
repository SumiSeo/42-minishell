/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/11 22:10:41 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_pipeline(t_parse *cmds_list, char **env_copy)
{
	int total_count = count_cmds(cmds_list);
	int i = 0;

	int tmp_in = dup(STDIN_FILENO);
	int tmp_out = dup(STDOUT_FILENO);

	if (tmp_in == -1 || tmp_out == -1)
	{
		perror("Stdin or stdout dup");
		exit(EXIT_FAILURE);
	}

	int fd_in;
	// open the file

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
	int *pids = malloc(total_count * sizeof(int));
	if (pids == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

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
		else
		{
			close(fd_out);
			pids[i] = fork_id;
		}
		cmds_list = cmds_list->next;
		i++;
	}
	i = 0;
	while (i < total_count)
	{
		if (waitpid(pids[i], NULL, 0) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free(pids);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
}