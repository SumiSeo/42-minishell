/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/17 16:25:15 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	parse_path(t_parse *cmds, char **env_copy)
// {
// 	if (cmds->path != NULL && cmds->cmd_array != NULL
// 		&& cmds->cmd_array[0] != NULL)
// 		execute_cmd(cmds, env_copy);
// 	else
// 		printf("Command '%s' not found\n", cmds->cmd_array[0]);
// }

// void	free_cmd_and_path(char *joined_cmd, char *joined_path)
// {
// 	free(joined_cmd);
// 	free(joined_path);
// }

// void	free_array(char **line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		free(line[i]);
// 		i++;
// 	}
// 	free(line);
// }

// void	execute_cmd(t_parse *cmds, char **env_copy)
// {
// 	int	i;

// 	i = 0;
// 	if (cmds->cmd_array[0] == (void *)0 && access(cmds->path, X_OK | F_OK) != 0)
// 	{
// 		ft_putstr_fd("Command not found\n", 2);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (access(cmds->path, X_OK | F_OK) == 0)
// 		execve(cmds->path, cmds->cmd_array, env_copy);
// 	else
// 		perror("ERROR");
// }
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

int	parse_path(char **cmds, char *path, char **env)
{
	(void)cmds;
	(void)path;
	(void)env;
	if (access(path, X_OK | F_OK) != 0)
	{
		printf("%s: Command not found\n", cmds[0]);
		return (0);
	}
	else
		return (1);
}
