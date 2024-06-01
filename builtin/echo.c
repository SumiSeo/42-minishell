/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:06:26 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/01 18:15:50 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_echo(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "echo";
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

int	print_echo(t_parse *cmds, int i, int nextline_flag)
{
	printf("TESTTEST\n");
	while (cmds->cmd_array[i])
	{
		printf("%s", cmds->cmd_array[i]);
		if ((cmds)->cmd_array[i])
			printf(" ");
		i++;
	}
	if (!nextline_flag)
	{
		printf("\n");
		return (2);
	}
	else
		return (1);
}
void	func_echo(t_parse *cmds)
{
	int	nextline_flag;
	int	i;

	nextline_flag = 0;
	i = 1;
	if (cmds->cmd_array[1] && cmds->cmd_array[1][0] == '-'
		&& cmds->cmd_array[1][1] == 'n')
	{
		nextline_flag = 1;
		i++;
	}
	else if (print_echo(cmds, i, nextline_flag) == 2)
		return ;
	if (cmds->cmd_array[2][0] == '-' && cmds->cmd_array[2][1] == 'n')
		i++;
	else
		i = 2;
	print_echo(cmds, i, nextline_flag);
}
