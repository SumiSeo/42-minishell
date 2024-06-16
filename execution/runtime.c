/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/16 13:31:18 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runtime_shell(t_parse *cmds_list, char **env_copy, t_data *data)
{
	t_pipe	*pipe_info;
	int		i;
	int		fork_id;

	t_parse *const head = cmds_list;
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
		if (getfile(cmds_list, pipe_info) > 0)
		{
			fork_id = fork();
			if (fork_id == -1)
				perror("fork");
			if (fork_id == 0)
			{
				redirection(cmds_list, pipe_info, i);
				parse_path(cmds_list, env_copy);
			}
			i++;
			if (cmds_list->infile_name)
				close(cmds_list->infile);
			if (cmds_list->outfile_token)
				close(cmds_list->outfile);
			if (i == pipe_info->total_cmds)
				break ;
			cmds_list = cmds_list->next;
		}
		else
			return ;
	}
	close_pipe_files(head, pipe_info);
	wait_pipe_files(head, pipe_info);
	free(pipe_info);
}

// void	exec_shell(t_parse *cmds_list, char **env_copy)
// {
// 	printf("EXec cshell \n");
// 	int fork_id = fork();
// 	if (fork_id < 0)
// 		exit_program("Fork failed");
// 	else if (fork_id == 0)
// 		parse_path(cmds_list, env_copy);
// 	wait(0);
// }