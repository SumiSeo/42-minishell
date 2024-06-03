/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/03 16:59:11 by sumseo           ###   ########.fr       */
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
	int i;
	i = 0;
	char *found_value;
	int len;
	len = ft_strlen(cmds->cmd_array[1]);

	if (!cmds->cmd_array[1])
		return ;
	else
	{
		while (env)
		{
			found_value = ft_strnstr(env->env_var, cmds->cmd_array[1], len);
			if (found_value != NULL)
				break ;
			env = env->next;
		}
	}
	printf("Check %s\n", found_value);
}