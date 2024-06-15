/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/15 16:34:58 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	getfile(t_parse *cmds_list)
{
	if (cmds_list == NULL)
	{
		fprintf(stderr, "cmds_list is NULL\n");
		return ;
	}
	if (cmds_list->infile_token && ft_strncmp(cmds_list->infile_token, "<<",
			2) == 0)
	{
		printf("heredoc\n");
	}
	else if (cmds_list->infile_token && ft_strncmp(cmds_list->infile_token, "<",
			1) == 0)
	{
		cmds_list->infile = open(cmds_list->infile_name, O_RDONLY);
	}
	if (cmds_list->outfile_token && ft_strncmp(cmds_list->outfile_token, ">>",
			2) == 0)
		cmds_list->outfile = open(cmds_list->outfile_name, O_RDWR | O_APPEND,
				0644);
	else if (cmds_list->outfile_token && ft_strncmp(cmds_list->outfile_token,
			">", 1) == 0)
		cmds_list->outfile = open(cmds_list->outfile_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
}
void	close_pipe_files(t_parse *cmds_list, t_pipe *pipe_info)
{
	int	i;

	i = 0;
	while (i < pipe_info->total_cmds)
	{
		if (cmds_list && cmds_list->prev)
		{
			if (cmds_list->prev->pipe_fdi >= 0)
				close(cmds_list->prev->pipe_fdi);
			if (cmds_list->prev->pipe_fdo >= 0)
				close(cmds_list->prev->pipe_fdo);
		}
		if (cmds_list)
			cmds_list = cmds_list->next;
		wait(0);
		i++;
	}
}

void	pipe_init(t_pipe *pipe_info, t_parse *cmds_list, int i, t_data *data)
{
	int	fd[2];

	if (data->has_pipe < 1)
		return ;
	else
	{
		if (i < pipe_info->total_cmds - 1)
		{
			if (pipe(fd) == -1)
				perror("Pipe");
			cmds_list->pipe_fdi = fd[0];
			cmds_list->pipe_fdo = fd[1];
			printf("@@@Pipe created\n");
		}
		else
			return ;
	}
}

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
		pipe_init(pipe_info, cmds_list, i, data);
		getfile(cmds_list);
		fork_id = fork();
		if (fork_id == -1)
			perror("fork");
		if (fork_id == 0)
		{
			redirection(cmds_list, pipe_info, i);
			parse_path(cmds_list, env_copy);
		}
		i++;
		if (i == pipe_info->total_cmds)
			break ;
		cmds_list = cmds_list->next;
	}
	close_pipe_files(cmds_list, pipe_info);
	free(pipe_info);
}
