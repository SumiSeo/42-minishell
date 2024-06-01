/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/01 18:09:57 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runtime_shell(t_parse *cmds_list)
{
	(void)cmds_list;
	;
	printf("RUNTIME SHELL CALLED\n");
	// getting datas simple cdms and piped cmdds
	// execute_pipeline(parsed_args_piped, *copy + 5, env);
	// if i do all check, execute command
}

void	exec_shell(t_parse *cmds_list, t_env *env)
{
	int j;

	j = 0;

	int fork_id = fork();
	if (fork_id < 0)
		exit_program("Fork failed");
	else if (fork_id == 0)
	{
		parse_path(cmds_list->cmd_array[0], env);
	}
	else
		wait(NULL);
}