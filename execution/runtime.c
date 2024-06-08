/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/08 21:14:29 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runtime_shell(t_parse *cmds_list, t_env *env_list, char **env_copy,
		t_data *data)
{
	// // if (data->has_pipe < 1)
	// // 	execute_redirection(cmds_list, env_copy);
	// else if (data->has_pipe > 0)
	execute_pipeline(cmds_list, env_list, env_copy, data);
}

void	exec_shell(t_parse *cmds_list, char **env_copy)
{
	int fork_id = fork();
	if (fork_id < 0)
		exit_program("Fork failed");
	else if (fork_id == 0)
		parse_path(cmds_list, env_copy);
	else
		wait(NULL);
}