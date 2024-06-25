/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/25 17:24:56 by sumseo           ###   ########.fr       */
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

void	init_child(t_parse *cmds_list, char **env_copy)
{
	if (getfile(cmds_list))
	{
		only_redirection(cmds_list);
		if (parse_path(cmds_list->cmd_array, cmds_list->path))
			execve(cmds_list->path, cmds_list->cmd_array, env_copy);
	}
}

void	exec_shell_builtin(t_parse *cmds_list, int builtin_check,
		t_env *env_list)
{
	if (getfile(cmds_list))
	{
		only_redirection(cmds_list);
		exec_builtin(builtin_check, cmds_list, env_list);
	}
}

void	exec_shell(t_parse *cmds_list, t_env *env_list, char **env_copy)
{
	int	builtin_check;
	int	fork_id;

	builtin_check = is_builtin(cmds_list);
	if (builtin_check > 0)
	{
		cmds_list->old_stdin = dup(STDIN_FILENO);
		cmds_list->old_stdout = dup(STDOUT_FILENO);
		exec_shell_builtin(cmds_list, builtin_check, env_list);
		dup2(cmds_list->old_stdout, STDOUT_FILENO);
		dup2(cmds_list->old_stdin, STDIN_FILENO);
		close(cmds_list->old_stdout);
		close(cmds_list->old_stdin);
	}
	else
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			init_child(cmds_list, env_copy);
			exit(0);
		}
		wait(0);
	}
}
