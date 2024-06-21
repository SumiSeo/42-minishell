/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/21 15:01:52 by sumseo           ###   ########.fr       */
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

void	func_exit(t_parse *cmds)
{
	int	i;

	i = 0;
	while (cmds->cmd_array[1][i])
	{
		if (ft_isalpha(cmds->cmd_array[1][i]))
		{
			printf("exit : %s: numeric argument required\n",
				cmds->cmd_array[1]);
			exit(1);
			break ;
		}
		i++;
	}
	if (cmds->cmd_array[1] && cmds->cmd_array[2])
	{
		printf("exit: too many arugments\n");
		exit(1);
		return ;
	}
	i = 0;
	while (cmds->cmd_array[1][i])
	{
		printf("%s\n", cmds->cmd_array[i]);
		if (!ft_isdigit(cmds->cmd_array[1][i]))
		{
			printf("exit : %s: numeric argument required\n",
				cmds->cmd_array[1]);
			exit(1);
			break ;
		}
		else
		{
			exit(1);
			printf("exit\n");
			return ;
		}
		i++;
	}
}
