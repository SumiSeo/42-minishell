/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/15 15:15:42 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_heredoc(t_parse *cmds_list, t_pipe *pipe_info)
{
	int		tmp;
	char	*str;
	size_t	len;

	(void)cmds_list;
	tmp = open("tmp", O_RDONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		str = get_next_line(0);
		if (!str)
			perror("get _next_line");
		len = ft_strlen(str);
		if (len > 0 && str[len - 1] == '\n')
			str[len - 1] = '\0';
		if (ft_strncmp(str, pipe_info->limiter,
				ft_strlen(pipe_info->limiter)) == 0
			&& ft_strlen(str) == ft_strlen(pipe_info->limiter))
		{
			free(str);
			break ;
		}
		free(str);
	}
}

void	only_redirection(t_parse *cmds_list)
{
	dup2(cmds_list->infile, STDIN_FILENO);
	close(cmds_list->infile);
	dup2(cmds_list->outfile, STDOUT_FILENO);
	close(cmds_list->outfile);
}

void	redirection(t_parse *cmds_list, t_pipe *pipe_info, char **env_copy,
		int i)
{
	(void)env_copy;
	(void)cmds_list;
	(void)i;
	if (!cmds_list || !pipe_info)
	{
		printf("cmds_list or pipe_info is NULL\n");
	}
	if (pipe_info->total_cmds == 1)
	{
		only_redirection(cmds_list);
		return ;
	}
	else if (i == 0)
	{
		if (cmds_list->infile_name)
		{
			dup2(cmds_list->infile, STDIN_FILENO);
			close(cmds_list->infile);
		}
		dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
		close(cmds_list->pipe_fdo);
		close(cmds_list->pipe_fdi);
	}
	else if (i == pipe_info->total_cmds - 1)
	{
		printf("Last command\n");
		printf("cmds_list->prev->pipe_fdi %d\n", cmds_list->prev->pipe_fdi);
		printf("cmds_list->prev->pipe_fdo %d\n", cmds_list->prev->pipe_fdo);
		if (cmds_list->outfile_token)
		{
			dup2(cmds_list->outfile, STDOUT_FILENO);
			close(cmds_list->outfile);
		}
		dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
		close(cmds_list->prev->pipe_fdi);
		close(cmds_list->prev->pipe_fdo);
	}
	// else
	// {
	// 	// middle command
	// 	if (cmds_list->infile_name)
	// 	{
	// 		dup2(cmds_list->infile, STDIN_FILENO);
	// 		close(cmds_list->infile);
	// 	}
	// 	if (cmds_list->outfile_name)
	// 	{
	// 		dup2(cmds_list->outfile, STDOUT_FILENO);
	// 		close(cmds_list->outfile);
	// 	}
	// 	dup2(cmds_list->prev->pipe_fdo, STDOUT_FILENO);
	// 	dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
	// 	close(cmds_list->prev->pipe_fdi);
	// 	close(cmds_list->prev->pipe_fdo);
	// }
}
