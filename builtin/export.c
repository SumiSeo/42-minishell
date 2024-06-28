/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:10 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/28 11:43:44 by sumseo           ###   ########.fr       */
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

t_env	*sort_env(t_env *env_copy, t_env *current)
{
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = env_copy;
		while (current && current->next != NULL)
		{
			if (ft_strncmp(current->env_var, current->next->env_var, 1) > 0)
			{
				tmp = current->env_var;
				current->env_var = current->next->env_var;
				current->next->env_var = tmp;
				swapped = 1;
			}
			current = current->next;
		}
	}
	current = env_copy;
	return (current);
}

void	export_without_args(t_env **env)
{
	t_env	*env_copy;
	t_env	*current;

	current = *env;
	env_copy = NULL;
	while (current)
	{
		push_env_list(&env_copy, current->env_var, ft_strlen(current->env_var));
		current = current->next;
	}
	current = sort_env(env_copy, current);
	while (current)
	{
		printf("export %s\n", current->env_var);
		current = current->next;
	}
}

int	check_variable(t_env **env, char *variable, char *value)
{
	char	*found_value;
	int		result;
	t_env	*current;

	result = 0;
	current = *env;
	while (current != NULL)
	{
		found_value = ft_strnstr(current->env_var, variable,
				strlen(current->env_var));
		if (found_value != NULL)
		{
			result = 1;
			replace_one_env(env, current->env_var, variable, value);
			break ;
		}
		current = current->next;
	}
	return (result);
}

void	func_export(t_parse *cmds, t_env **env)
{
	int		i;
	char	*value;
	char	*variable_join;
	char	*final_value;

	if (!cmds->cmd_array[1])
	{
		export_without_args(env);
		return ;
	}
	i = 1;
	while (cmds->cmd_array[i])
	{
		if (cmds->cmd_array[i][0] == '_' || ft_isalpha(cmds->cmd_array[i][0]))
		{
			variable_join = func_variable(cmds->cmd_array[i]);
			value = func_value(cmds->cmd_array[i]);
			final_value = func_join_words(variable_join, value);
			if (!check_variable(env, variable_join, value))
				push_env_list(env, final_value, ft_strlen(final_value));
		}
		else
			printf("not valid in this context %s\n", cmds->cmd_array[i]);
		i++;
	}
}
