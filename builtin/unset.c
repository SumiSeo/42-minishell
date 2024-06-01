/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/01 18:06:30 by sumseo           ###   ########.fr       */
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
	(void)cmds;
	(void)env;
	printf("unset");
	// char *a = getenv("user");
	printf("GETEMV %s\n", getenv("TERM"));
}