/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:41:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/25 20:59:44 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char **cmds)
{
	if (is_echo(cmds[0]) == 1)
		func_echo(cmds);
	else if (is_pwd(cmds[0]))
	{
		printf("Pwd");
	}
	else if (is_cd(cmds[0]))
	{
		printf("cd");
	}
	else if (is_env(cmds[0]))
	{
		printf("env");
	}
	else if (is_exit(cmds[0]))
	{
		printf("exit");
	}
	else if (is_pwd(cmds[0]))
	{
		printf("pwd");
	}
	else if (is_unset(cmds[0]))
	{
		printf("unset");
	}
	else if (is_export(cmds[0]))
	{
		printf("export");
	}
	else
		return (0);
	return (1);
}

