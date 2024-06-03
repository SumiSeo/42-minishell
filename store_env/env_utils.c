/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:20:22 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/03 20:57:09 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_one_env(t_env **env_list, char *variable)
{
	t_env	*current;
	char	*variable_and;

	variable_and = ft_strjoin(variable, "=");
	current = *env_list;
	while (current != NULL)
	{
		if (ft_strnstr(current->env_var, variable_and,
				ft_strlen(current->env_var)))
		{
			free(current->env_var);
			current->prev->next = current->next;
		}
		current = current->next;
	}
}

void	replace_one_env(t_env *env_list, char *env_val, char *variable,
		char *value)
{
	char	*new_var;

	new_var = ft_strjoin(variable, value);
	if (new_var == NULL)
	{
		perror("Failed to allocate memory for new_var");
		return ;
	}
	while (env_list)
	{
		if (env_list->env_var == env_val)
		{
			free(env_list->env_var);
			env_list->env_var = new_var;
			return ;
		}
		env_list = env_list->next;
	}
}
