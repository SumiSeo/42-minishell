/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:20:22 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/03 18:34:25 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_one_env(t_env *env_list, char *env_val, const char *str)
{
	(void)str;
	while (env_list)
	{
		if (env_list->env_var == env_val)
		{
			env_list->env_var = "CHECK";
		}
		env_list = env_list->next;
	}
}

void	replace_one_env(t_env *env_list, char *env_val, char *variable,
		char *value)
{
	char *new_var;
	new_var = ft_strjoin(variable, value);

	while (env_list)
	{
		if (env_list->env_var == env_val)
		{
			env_list->env_var = new_var;
		}
		env_list = env_list->next;
	}
}