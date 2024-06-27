/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:20:22 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/27 18:32:23 by sumseo           ###   ########.fr       */
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

void	replace_one_env(t_env **env_list, char *env_val, char *variable,
		char *value)
{
	t_env	*current;
	char	*new_var;

	new_var = malloc(strlen(variable) + strlen(value) + 2);
	if (new_var == NULL)
	{
		perror("Failed to allocate memory for new_var");
		return ;
	}
	strcpy(new_var, variable);
	strcat(new_var, value);
	current = *env_list;
	while (current != NULL)
	{
		if (strcmp(current->env_var, env_val) == 0)
		{
			free(current->env_var);
			current->env_var = new_var;
			return ;
		}
		current = current->next;
	}
	free(new_var);
}
