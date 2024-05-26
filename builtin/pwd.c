/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:09:42 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 17:06:03 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pwd(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "pwd";
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

void	func_pwd(char **cmds)
{
	int nextline_flag;
	nextline_flag = 0;

	int i = 1;
	if (cmds[1] && cmds[1][0] == '-' && cmds[1][1] == 'n')
	{
		nextline_flag = 1;
		i = 2;
	}

	while (cmds[i])
	{
		printf("%s", cmds[i]);
		if (cmds[i + 1])
			printf(" ");
		i++;
	}
	if (!nextline_flag)
		printf("\n");
}