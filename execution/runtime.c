/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/23 22:49:48 by sumseo           ###   ########.fr       */
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
	(void)i;
	(void)pipe_info;
	// if (getfile(cmds_list))
	// {
	if (parse_path(cmds_list->cmd_array, cmds_list->path))
	{
		redirection(cmds_list, pipe_info, i);
		execve(cmds_list->path, cmds_list->cmd_array, env_copy);
		exit(EXIT_FAILURE);
	}
	else
		exit(EXIT_FAILURE);
	// }
	// else	close_no_file(cmds_list);
}

void	runtime_shell(t_parse *cmds_list, char **env_copy, t_data *data,
		t_env *env_list)
{
	t_pipe	*pipe_info;
	int		fork_id;
	int		i;
	t_parse	*head;
	int		builtin_check;

	(void)env_list;
	printf("Runtime shell called\n");
	head = cmds_list;
	i = 0;
	pipe_info = malloc(sizeof(t_pipe));
	if (pipe_info == NULL)
		pipe_null_check();
	pipe_info->total_cmds = count_cmds(cmds_list);
	while (i < pipe_info->total_cmds)
	{
		pipe_init(pipe_info, cmds_list, i, data);
		fork_id = fork();
		if (fork_id == -1)
			perror("fork");
		if (fork_id == 0)
		{
			builtin_check = is_builtin(cmds_list);
			if (getfile(cmds_list))
			{
				if (builtin_check > 0)
				{
					redirection(cmds_list, pipe_info, i);
					exec_builtin(builtin_check, cmds_list, env_list);
				}
				else
				{
					init_child_pipe(cmds_list, pipe_info, env_copy, i);
					exit(0);
				}
			}
			else
				close_no_file(cmds_list);
		}
		if (cmds_list->next != NULL)
			close(cmds_list->pipe_fdo);
		if (cmds_list->prev != NULL)
			close(cmds_list->prev->pipe_fdi);
		i++;
		cmds_list = cmds_list->next;
	}
	close_parent(head, pipe_info);
}
