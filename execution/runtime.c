/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/21 16:20:11 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_null_check(void)
{
	perror("pipe_info_malloc");
	exit(EXIT_FAILURE);
}

void	close_parent(t_parse *head, t_pipe *pipe_info)
{
	close_pipe_files(head);
	wait_pipe_files(pipe_info);
	free(pipe_info);
}

void	close_no_file(t_parse *cmds_list)
{
	close(cmds_list->pipe_fdi);
	close(cmds_list->pipe_fdo);
	exit(EXIT_FAILURE);
}

void	init_child_pipe(t_parse *cmds_list, t_pipe *pipe_info, char **env_copy,
		int i)
{
	if (getfile(cmds_list, pipe_info))
	{
		if (parse_path(cmds_list->cmd_array, cmds_list->path, env_copy))
		{
			redirection(cmds_list, pipe_info, i);
			execve(cmds_list->path, cmds_list->cmd_array, env_copy);
			exit(EXIT_FAILURE);
		}
		else
			exit(EXIT_FAILURE);
	}
	else
		close_no_file(cmds_list);
}

void	runtime_shell(t_parse *cmds_list, char **env_copy, t_data *data)
{
	t_pipe	*pipe_info;
	int		fork_id;
	int		i;
	t_parse	*head;

	head = cmds_list;
	pipe_info = malloc(sizeof(t_pipe));
	if (pipe_info == NULL)
		pipe_null_check();
	i = 0;
	pipe_info->total_cmds = count_cmds(cmds_list);
	while (i < pipe_info->total_cmds)
	{
		pipe_init(pipe_info, cmds_list, i, data);
		fork_id = fork();
		if (fork_id == -1)
			perror("fork");
		if (fork_id == 0)
			init_child_pipe(cmds_list, pipe_info, env_copy, i);
		if (cmds_list->next != NULL)
			close(cmds_list->pipe_fdo);
		i++;
		cmds_list = cmds_list->next;
	}
	close_parent(head, pipe_info);
}
