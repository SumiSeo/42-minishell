/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/03 20:50:08 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_unset(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "unset";
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

void	func_unset(t_parse *cmds, t_env *env)
{
	int		i;
	char	*found_value;

	i = 0;
	if (!cmds->cmd_array[1])
		return ;
	else
	{
		while (env)
		{
			found_value = ft_strnstr(env->env_var, cmds->cmd_array[1],
					ft_strlen(cmds->cmd_array[1]));
			if (found_value != NULL)
			{
				delete_one_env(&env, cmds->cmd_array[1]);
				break ;
			}
			env = env->next;
		}
	}
}
