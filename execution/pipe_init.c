/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/14 16:31:02 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_fork_pids(t_pipe *pipe_info)
{
	int	i;

	i = 0;
	while (i < pipe_info->total_cmds)
	{
		if (waitpid(pipe_info->pids[i], NULL, 0) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	free(pipe_info->pids);
}

// void	execute_pipeline(t_parse *cmds_list, char **env_copy)
// {
// 	t_pipe	*pipe_info;
// 	int		i;
// 	int		fd_out;
// 	int		fork_id;
// 	int		fdpipe[2];

// 	pipe_info = malloc(sizeof(t_pipe));
// 	if (pipe_info == NULL)
// 	{
// 		perror("pipe_info_malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	init_pipe(pipe_info, cmds_list);
// 	i = 0;
// 	while (i < pipe_info->total_cmds)
// 	{
// 		dup2(pipe_info->fdi, STDIN_FILENO);
// 		close(pipe_info->fdi);
// 		if (i == pipe_info->total_cmds - 1)
// 		{
// 			if (cmds_list->outfile_name && cmds_list->outfile_token)
// 			{
// 				fd_out = open(cmds_list->outfile_name,
// 						O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 				if (fd_out == -1)
// 					printf("What happed\n");
// 			}
// 			else
// 			{
// 				fd_out = dup(pipe_info->tmp_out);
// 			}
// 		}
// 		else
// 		{
// 			if (pipe(fdpipe) == -1)
// 			{
// 				perror("pipe");
// 				exit(EXIT_FAILURE);
// 			}
// 			pipe_info->fdi = fdpipe[READEND];
// 			fd_out = fdpipe[WRITEEND];
// 		}
// 		dup2(fd_out, STDOUT_FILENO);
// 		close(fd_out);
// 		fork_id = fork();
// 		if (fork_id == 0)
// 		{
// 			parse_path(cmds_list, env_copy);
// 			exit(EXIT_FAILURE);
// 		}
// 		else
// 		{
// 			close(fd_out);
// 			pipe_info->pids[i] = fork_id;
// 		}
// 		cmds_list = cmds_list->next;
// 		i++;
// 	}
// 	free_fork_pids(pipe_info);
// 	dup2(pipe_info->tmp_in, STDIN_FILENO);
// 	dup2(pipe_info->tmp_out, STDOUT_FILENO);
// 	close(pipe_info->tmp_in);
// 	close(pipe_info->tmp_out);
// 	free(pipe_info);
// }

void	pipe_init(t_pipe *pipe_info, int i, t_data *data)
{
	int	pipe_id;

	if (data->has_pipe < 1)
	{
		pipe_info->only_redirect = 1;
		return ;
	}
	if (i == 0)
	{
		pipe_info->is_first_cmd = 1;
	}
	else if (i == pipe_info->total_cmds - 1)
	{
		pipe_info->is_last_cmd = 1;
	}
	else
		pipe_info->is_middle_cmd = 1;
	pipe_id = pipe(pipe_info->pipefd);
	if (pipe_id == -1)
		perror("pipe");
	else
	{
		printf("Pipe created \n");
	}
}

void	execute_pipeline(t_parse *cmds_list, char **env_copy, t_data *data)
{
	t_pipe	*pipe_info;
	int		i;
	int		fork_id;

	pipe_info = malloc(sizeof(t_pipe));
	if (pipe_info == NULL)
	{
		perror("pipe_info_malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	pipe_info->total_cmds = count_cmds(cmds_list);
	while (i < pipe_info->total_cmds)
	{
		pipe_init(pipe_info, i, data);
		getfile(cmds_list, pipe_info);
		fork_id = fork();
		if (fork_id == -1)
			perror("fork");
		if (fork_id == 0)
		{
			redirection(cmds_list, pipe_info, env_copy, i);
			printf("Yo");
			parse_path(cmds_list, env_copy);
		}
		else
		{
			waitpid(fork_id, NULL, 0);
		}
		cmds_list = cmds_list->next;
		i++;
	}
	free(pipe_info);
}
