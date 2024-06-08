/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:41:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/08 17:48:38 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_parse *cmds, t_env *env)
{
	printf("Check\n");
	if (is_echo(cmds->cmd_array[0]) == 1)
		func_echo(cmds);
	else if (is_pwd(cmds->cmd_array[0]) == 1)
		func_pwd(cmds);
	else if (is_cd(cmds->cmd_array[0]) == 1)
		func_cd(cmds);
	else if (is_env(cmds->cmd_array[0]) == 1)
		func_env(cmds, env);
	else if (is_exit(cmds->cmd_array[0]) == 1)
		func_exit(cmds);
	else if (is_unset(cmds->cmd_array[0]))
		func_unset(cmds, env);
	else if (is_export(cmds->cmd_array[0]))
		func_export(cmds, env);
	else
		return (0);
	return (1);
}
