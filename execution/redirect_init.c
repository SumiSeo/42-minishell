/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/14 20:35:09 by sumseo           ###   ########.fr       */
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
void	getfile(t_parse *cmds_list, t_pipe *pipe_info)
{
	printf("check\n");
	if (cmds_list == NULL)
	{
		fprintf(stderr, "cmds_list is NULL\n");
		return ;
	}
	(void)pipe_info;
	if (cmds_list->infile_token && ft_strncmp(cmds_list->infile_token, "<<",
			2) == 0)
	{
		// pipe_info->limiter = cmds_list->infile_name;
		// open_heredoc(cmds_list, pipe_info);
		printf("heredoc\n");
	}
	else if (cmds_list->infile_token && ft_strncmp(cmds_list->infile_token, "<",
			1) == 0)
	{
		printf("normal infile\n");
		cmds_list->infile = open(cmds_list->infile_name, O_RDONLY);
	}
	else
	{
		printf("STANDARD INPUT\n");
		cmds_list->infile = dup(STDIN_FILENO);
	}
	if (cmds_list->outfile_token && ft_strncmp(cmds_list->outfile_token, ">>",
			2) == 0)
	{
		printf("append outfile\n");
		cmds_list->outfile = open(cmds_list->outfile_name, O_RDWR | O_APPEND,
				0644);
	}
	else if (cmds_list->outfile_token && ft_strncmp(cmds_list->outfile_token,
			">", 1) == 0)
	{
		printf("normal outfile\n");
		cmds_list->outfile = open(cmds_list->outfile_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	else if (!cmds_list->outfile_token)
	{
		printf("STANDARD OUTPUT\n");
		cmds_list->outfile = dup(STDOUT_FILENO);
	}
}

void	only_redirection(t_parse *cmds_list, t_pipe *pipe_info)
{
	(void)pipe_info;
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
		printf("only\n");
		only_redirection(cmds_list, pipe_info);
		return ;
	}
	else if (i == 0)
	{
		printf("First command\n");
		close(cmds_list->outfile);
		printf("Check fdi %d \n ", cmds_list->pipe_fdi);
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
		if (cmds_list->outfile_token)
		{
			dup2(cmds_list->outfile, STDOUT_FILENO);
			close(cmds_list->outfile);
			close(cmds_list->pipe_fdo);
		}
		else
		{
			dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
			close(cmds_list->pipe_fdo);
		}
	}
	else if (i == pipe_info->total_cmds - 1)
	{
		printf("Last command\n");
		close(cmds_list->prev->pipe_fdo);
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
		if (cmds_list->infile_token)
		{
			dup2(cmds_list->infile, STDIN_FILENO);
			close(cmds_list->infile);
			close(cmds_list->prev->pipe_fdi);
		}
		else
		{
			dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
			close(cmds_list->prev->pipe_fdi);
		}
	}
	// else
	// {
	// 	printf("Middle command\n");
	// 	if (cmds_list->infile_token)
	// 	{
	// 		dup2(cmds_list->prev, STDIN_FILENO);
	// 		close(pipe_info->fdi);
	// 		close(pipe_info->pipefd[0]);
	// 	}
	// 	else
	// 	{
	// 		dup2(pipe_info->pipefd[0], STDIN_FILENO);
	// 		close(pipe_info->pipefd[0]);
	// 	}
	// 	if (cmds_list->outfile_token)
	// 	{
	// 		dup2(pipe_info->fdo, STDOUT_FILENO);
	// 		close(pipe_info->fdo);
	// 		close(pipe_info->pipefd[1]);
	// 	}
	// 	else
	// 	{
	// 		dup2(pipe_info->pipefd[1], STDOUT_FILENO);
	// 		close(pipe_info->pipefd[1]);
	// 	}
}
