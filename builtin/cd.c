/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/01 19:05:38 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_cd(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "cd";
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

void	func_cd(t_parse *cmds)
{
	char	*rel_paths[2];
	int		path_int;
	int		i;
	int		is_relative;

	path_int = 0;
	rel_paths[0] = "..";
	rel_paths[1] = ".";
	i = 0;
	is_relative = 0;
	if (!cmds->cmd_array[1])
		return ;
	else
	{
		while (i < 4)
		{
			if (strcmp(cmds->cmd_array[1], rel_paths[i]) == 0)
			{
				path_int = i + 1;
				is_relative = 1;
				break ;
			}
			i++;
		}
	}
	if (is_relative == 1)
		func_relative_cd(path_int);
	else
		func_absolute_cd(cmds);
}

void	func_relative_cd(int path_int)
{
	if (path_int == 1)
		chdir("..");
	else if (path_int == 2)
		chdir(".");
}

void	func_absolute_cd(t_parse *cmds)
{
	printf("CMDS %s\n", cmds->cmd_array[1]);
	chdir(cmds->cmd_array[1]);
}
