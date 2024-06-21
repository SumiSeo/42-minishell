/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/21 16:01:30 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runtime_shell(t_parse *cmds_list, char **env_copy, t_data *data)
{
	printf("runtime shell called\n");
	execute_pipeline(cmds_list, env_copy, data);
}

void	exec_shell(t_parse *cmds_list, char **env_copy)
{
	int fork_id = fork();
	if (fork_id < 0)
		exit_program("Fork failed");
	else if (fork_id == 0)
		parse_path(cmds_list, env_copy);
	wait(0);
	wait(0);
}