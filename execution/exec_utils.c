/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 16:38:26 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_path(char *first_cmd, char *path, char **env)
{
	char	**arr;
	char	**cmds;

	arr = ft_split(path, ':');
	cmds = parse_cmd(first_cmd);
	if (cmds != NULL && cmds[0] != NULL)
	{
		execute_cmd(cmds, arr, env);
		free(cmds);
		free_array(cmds);
	}
	free_array(arr);
}

char	**parse_cmd(char *cmd)
{
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	if (cmds == NULL || cmds[0] == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		free(cmds);
		free_array(cmds);
		return (NULL);
	}
	return (cmds);
}
void	free_cmd_and_path(char *joined_cmd, char *joined_path)
{
	free(joined_cmd);
	free(joined_path);
}

void	free_array(char **line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

void	execute_cmd(char **cmds, char **arr, char **env)
{
	int i;
	char *joined_path;
	char *joined_cmd;

	i = 0;
	if (env[0] == (void *)0 && access(cmds[0], X_OK | F_OK) != 0)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (access(cmds[0], X_OK | F_OK) == 0)
	{
		free_array(arr);
		execve(cmds[0], cmds, env);
	}
	while (arr[i])
	{
		joined_cmd = ft_strjoin("/", cmds[0]);
		joined_path = ft_strjoin(arr[i], joined_cmd);
		if (access(joined_path, X_OK | F_OK) == 0)
			execve(joined_path, cmds, env);
		free_cmd_and_path(joined_cmd, joined_path);
		i++;
	}
	perror("ERROR");
}