/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/30 17:36:48 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_exit(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "exit";
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

void	func_exit(t_parser *cmds)
{
	int nextline_flag;
	nextline_flag = 0;
	int i;
	i = 1;
	(void)cmds;
	if (cmds->str[1] && cmds->str[1][0] == '-' && cmds->str[1][1] == 'n')
	{
		nextline_flag = 1;
		i++;
	}

	while (cmds->str[i])
	{
		printf("%s", cmds->str[i]);
		if ((cmds)->str[i])
			printf(" ");
		i++;
	}

	if (!nextline_flag)
		printf("\n");
}