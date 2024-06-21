/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/21 15:25:29 by sumseo           ###   ########.fr       */
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

void	control_alpha(char *s)
{
	printf("exit : %s: numeric argument required\n", s);
	exit(1);
}

void	control_many_args(void)
{
	printf("exit : too many arugments\n");
	exit(1);
}

void	normal_exit(void)
{
	printf("exit\n");
	exit(1);
}
void	func_exit(t_parse *cmds)
{
	int	i;

	i = 0;
	while (cmds->cmd_array[1][i])
	{
		if (ft_isalpha(cmds->cmd_array[1][i]))
			control_alpha(cmds->cmd_array[1]);
		i++;
	}
	if (cmds->cmd_array[1] && cmds->cmd_array[2])
	{
		control_many_args();
		return ;
	}
	i = 0;
	while (cmds->cmd_array[1][i])
	{
		if (!ft_isdigit(cmds->cmd_array[1][i]))
			control_alpha(cmds->cmd_array[1]);
		else
			normal_exit();
		i++;
	}
}
