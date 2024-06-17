/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/17 16:05:03 by sumseo           ###   ########.fr       */
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
	if (cmds_list->infile)
	{
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
	}
	if (cmds_list->outfile)
	{
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
	}
}

void	first_cmd(t_parse *cmds_list)
{
	if (cmds_list->infile_name)
	{
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
	}
	if (cmds_list->outfile_name)
	{
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
	}
	else
		dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
	close(cmds_list->pipe_fdo);
	close(cmds_list->pipe_fdi);
}
void	last_cmd(t_parse *cmds_list)
{
	if (cmds_list->outfile_token)
	{
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
	}
	if (cmds_list->infile_name)
	{
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
	}
	else
	{
		dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
	}
	close(cmds_list->prev->pipe_fdi);
	close(cmds_list->prev->pipe_fdo);
}

void	middle_cmd(t_parse *cmds_list)
{
	if (cmds_list->infile_name)
	{
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
	}
	else
	{
		dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
	}
	if (cmds_list->outfile_token)
	{
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
	}
	else
	{
		dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
	}
	close(cmds_list->pipe_fdi);
	close(cmds_list->pipe_fdo);
	close(cmds_list->prev->pipe_fdi);
	close(cmds_list->prev->pipe_fdo);
}

void	redirection(t_parse *cmds_list, t_pipe *pipe_info, int i)
{
	if (!cmds_list || !pipe_info)
		perror("cmds_list or pipe_info is NULL\n");
	if (pipe_info->total_cmds == 1)
	{
		only_redirection(cmds_list);
		return ;
	}
	else if (i == 0)
		first_cmd(cmds_list);
	else if (i == pipe_info->total_cmds - 1)
		last_cmd(cmds_list);
	else
		middle_cmd(cmds_list);
}
