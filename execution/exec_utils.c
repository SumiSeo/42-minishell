/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:11 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/24 17:10:02 by sumseo           ###   ########.fr       */
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

void	exec_shell(t_parse *cmds_list, t_env *env_list, char **env_copy,
		t_data *data)
{
	int		builtin_check;
	t_parse	*head;
	int		fork_id;
	int		old_stdin;
	int		old_stdout;

	(void)data;
	head = cmds_list;
	builtin_check = is_builtin(cmds_list);
	if (builtin_check > 0)
	{
		printf("HERE\n");
		old_stdin = dup(STDIN_FILENO);
		old_stdout = dup(STDOUT_FILENO);
		if (getfile(cmds_list))
		{
			only_redirection(cmds_list);
			exec_builtin(builtin_check, cmds_list, env_list);
		}
		dup2(old_stdout, STDOUT_FILENO);
		dup2(old_stdin, STDIN_FILENO);
		close(old_stdout);
		close(old_stdin);
	}
	else
	{
		fork_id = fork();
		if (fork_id == -1)
			printf("fork failed\n");
		if (fork_id == 0)
		{
			if (getfile(cmds_list))
			{
				only_redirection(cmds_list);
				if (parse_path(cmds_list->cmd_array, cmds_list->path))
					execve(cmds_list->path, cmds_list->cmd_array, env_copy);
			}
			exit(0);
		}
		wait(0);
	}
}
