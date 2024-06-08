/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/07 21:09:30 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runtime_shell(t_parse *cmds_list, t_env *env_list, char **env_copy,
		t_data *data)
{
	printf("cmds check Infile EXIST: %d\n", cmds_list->infile_exist);
	printf("cmds check Infile NAME : %s\n", cmds_list->infile_name);
	printf("cmds check Infile TOKEN : %s\n", cmds_list->infile_token);
	printf("cmds check Infile ACCESS : %d\n", cmds_list->infile_access);
	// if (data->has_pipe < 1)
	// 	execute_redirection(cmds_list, env_copy);
	// else if (data->has_pipe > 0)
	execute_pipeline(cmds_list, env_list, env_copy, data);
}

void	exec_shell(t_parse *cmds_list, char **env_copy)
{
	// I dont' think i need for here but I am just leaving it here
	printf("Execute direct command \n");
	int fork_id = fork();
	if (fork_id < 0)
		exit_program("Fork failed");
	else if (fork_id == 0)
		parse_path(cmds_list, env_copy);
	else
		wait(NULL);
}