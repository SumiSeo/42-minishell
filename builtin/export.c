/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:10 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/03 18:35:12 by sumseo           ###   ########.fr       */
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

void	export_without_args(t_env *env)
{
	t_env	*env_copy;
	t_env	*current;
	char	*tmp;
	int		swapped;

	current = env;
	env_copy = NULL;
	while (current)
	{
		push_env_list(&env_copy, current->env_var, ft_strlen(current->env_var));
		current = current->next;
	}
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
	while (current)
	{
		printf("export %s\n", current->env_var);
		current = current->next;
	}
}

int	check_variable(t_parse *cmds, t_env *env, char *variable, char *value)
{
	char	*found_value;
	int		result;

	result = 0;
	(void)cmds;
	while (env)
	{
		found_value = ft_strnstr(env->env_var, variable, ft_strlen(variable));
		if (found_value != NULL)
		{
			result = 1;
			replace_one_env(env, env->env_var, variable, value);
			break ;
		}
		env = env->next;
	}
	return (result);
}
// void	replace_env_value(t_env *env, char *variable, char *value)
// {
// 	printf("It already exists \n");
// }

void	func_export(t_parse *cmds, t_env *env)
{
	char *variable;
	char *value;
	char *new_var;
	int len;

	if (!cmds->cmd_array[1])
	{
		export_without_args(env);
		return ;
	}
	variable = ft_strdup(cmds->cmd_array[1]);
	value = ft_strdup(cmds->cmd_array[2]);
	if (check_variable(cmds, env, variable, value))
		return ;
	else
	{
		if (variable[0] != '\0' && value[0] != '\0')
		{
			new_var = ft_strjoin(variable, value);
			len = ft_strlen(new_var);
			push_env_list(&env, new_var, len);
		}
		else
			return ;
	}
}