/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/25 16:45:45 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runtime_shell(char **simple_cmds, char **pipe_cmds)
{
	int	i;
	int	j;

	printf("RUNTIME SHELL CALLED\n");
	// getting datas simple cdms and piped cmdds
	// execute_pipeline(parsed_args_piped, *copy + 5, env);
	// if i do all check, execute command
	i = 0;
	while (simple_cmds[i])
	{
		printf("each args %s\n", simple_cmds[i]);
		i++;
	}
	j = 0;
	while (pipe_cmds[j])
	{
		printf("each piped args %s\n", pipe_cmds[j]);
		j++;
	}
}

void	exec_shell(char **simple_cmds)
{
	// There is no piipe in this cmds
	printf("EXEC SHELL CALLED\n");
	int i = 0;
	while (simple_cmds[i])
	{
		printf("each args %s\n", simple_cmds[i]);
		i++;
	}
	// int id = fork();
	// if(id == )
}