/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:10 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/01 18:14:43 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_export(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "export";
	while (str[i] && echo[i])
	{
		if (str[i] == echo[i])
			i++;
		else
			return (0);
	}
	if (str[i] == '\0' && echo[i] == '\0')
		return (1);
	return (0);
}

void	func_export(t_parse *cmds, t_env *env)
{
	char *variable;
	char *value;
	char *new_var;
	int len;
	// int i = 0;

	if (!cmds->cmd_array[1])
	{
		// list of exports ? need to check!
		printf("Export arguments dont exits");
		return ;
	}
	variable = ft_strdup(cmds->cmd_array[1]);
	value = ft_strdup(cmds->cmd_array[2]);

	if (variable[0] != '\0' && value[0] != '\0')
	{
		new_var = ft_strjoin(variable, value);
		len = ft_strlen(new_var);
		push_env_list(&env, new_var, len);
	}
	else
		return ;
}