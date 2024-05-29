/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 18:52:10 by sumseo           ###   ########.fr       */
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

void	func_cd(char **cmds)
{
	char	*rel_paths[3];
	int		path_int;
	int		i;

	path_int = 0;
	rel_paths[0] = "..";
	rel_paths[1] = ".";
	rel_paths[2] = "~";
	i = 0;
	if (!cmds[1])
		return ;
	else
	{
		while (i < 4)
		{
			if (strcmp(cmds[1], rel_paths[i]) == 0)
			{
				path_int = i + 1;
				break ;
			}
			i++;
		}
	}
	func_relative_cd(path_int);
}

void	func_relative_cd(int path_int)
{
	if (path_int == 1)
		chdir("..");
	else if (path_int == 2)
		chdir(".");
	else if (path_int == 3)
		chdir("/home");
}

void	func_absolute_cd(int path_int)
{
	if (path_int == 1)
		chdir("..");
	else if (path_int == 2)
		chdir(".");
	else if (path_int == 3)
		chdir("/home");
}
