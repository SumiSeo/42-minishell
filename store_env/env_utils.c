/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:20:22 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/27 21:15:45 by sumseo           ###   ########.fr       */
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
			if (*env_list == current)
				*env_list = current->next;
			if (current->prev != NULL)
				current->prev->next = current->next;
			free(current);
			free(variable_and);
			return ;
		}
		current = current->next;
	}
}

void	replace_one_env(t_env **env_list, char *env_val, char *variable,
		char *value)
{
	t_env	*current;
	char	*new_var;
	size_t	new_var_len;

	current = *env_list;
	new_var_len = strlen(variable) + strlen(value) + 1;
	new_var = malloc(new_var_len);
	if (new_var == NULL)
	{
		perror("Failed to allocate memory for new_var");
		return ;
	}
	snprintf(new_var, new_var_len, "%s%s", variable, value);
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
