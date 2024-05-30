/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:41:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/30 20:21:23 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_parser *cmds)
{
	if (is_echo(cmds->str[0]) == 1)
		func_echo(cmds);
	else if (is_pwd(cmds->str[0]) == 1)
		func_pwd(cmds);
	else if (is_cd(cmds->str[0]) == 1)
		func_cd(cmds);
	// else if (is_env(cmds[0]))
	// {
	// 	printf("env");
	// }
	else if (is_exit(cmds->str[0]) == 1)
		func_exit(cmds);
	// else if (is_unset(cmds[0]))
	// {
	// 	printf("unset");
	// }
	// else if (is_export(cmds[0]))
	// {
	// 	printf("export");
	// }
	else
	{
		return (0);
	}
	return (1);
}
