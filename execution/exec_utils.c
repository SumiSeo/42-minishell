/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/23 20:20:58 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	parse_path(char **cmds, char *path)
{
	if (access(path, X_OK | F_OK) != 0)
	{
		printf("%s: Command not found\n", cmds[0]);
		return (0);
	}
	else
		return (1);
}

void	exec_shell(t_parse *cmds_list, t_env *env_list, char **env_copy)
{
	int		builtin_check;
	t_parse	*head;
	int		fork_id;

	head = cmds_list;
	printf("****only one command or only one command with redirection***\n");
	fork_id = fork();
	if (fork_id == -1)
		printf("fork failed\n");
	if (fork_id == 0)
	{
		builtin_check = is_builtin(cmds_list);
		if (getfile(cmds_list))
		{
			only_redirection(cmds_list);
			if (builtin_check > 0)
				exec_builtin(builtin_check, cmds_list, env_list);
			else
				execve(cmds_list->path, cmds_list->cmd_array, env_copy);
		}
		if (cmds_list->infile)
			close(cmds_list->infile);
		if (cmds_list->outfile)
			close(cmds_list->outfile);
		exit(0);
	}
	if (cmds_list->infile)
		close(cmds_list->infile);
	if (cmds_list->outfile)
		close(cmds_list->outfile);
	wait(0);
}
