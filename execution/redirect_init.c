/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/14 19:07:29 by sumseo           ###   ########.fr       */
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
	if (cmds_list->infile_token && ft_strncmp(cmds_list->infile_token, "<<",
			2) == 0)
	{
		pipe_info->limiter = cmds_list->infile_name;
		// open_heredoc(cmds_list, pipe_info);
	}
	else if (cmds_list->infile_token && ft_strncmp(cmds_list->infile_token, "<",
			1) == 0)
	{
		printf("normal infile\n");
		pipe_info->fdi = open(cmds_list->infile_name, O_RDONLY);
	}
	else
	{
		pipe_info->fdi = dup(STDIN_FILENO);
	}
	if (cmds_list->outfile_token && ft_strncmp(cmds_list->outfile_token, ">>",
			2) == 0)
	{
		printf("append outfile\n");
		pipe_info->fdo = open(cmds_list->outfile_name, O_RDWR | O_APPEND, 0644);
	}
	else if (cmds_list->outfile_token && ft_strncmp(cmds_list->outfile_token,
			">", 1) == 0)
	{
		pipe_info->fdo = open(cmds_list->outfile_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (pipe_info->fdo == -1)
			perror("fdo");
	}
	else
		pipe_info->fdo = dup(STDOUT_FILENO);
}

void	only_redirection(t_pipe *pipe_info)
{
	dup2(pipe_info->fdi, STDIN_FILENO);
	close(pipe_info->fdi);
	dup2(pipe_info->fdo, STDOUT_FILENO);
	close(pipe_info->fdo);
}

void	redirection(t_parse *cmds_list, t_pipe *pipe_info, char **env_copy,
		int i)
{
	(void)env_copy;
	(void)cmds_list;
	if (!cmds_list || !pipe_info)
	{
		printf("cmds_list or pipe_info is NULL\n");
	}
	if (pipe_info->total_cmds == 1)
	{
		only_redirection(pipe_info);
		return ;
	}
	(void)i;
	// if (i == 0)
	// {
	// 	printf("First command\n");
	// 	close(cmds_list->fd[0]);
	// 	dup2(pipe_info->fdi, STDIN_FILENO);
	// 	close(pipe_info->fdi);
	// 	if (cmds_list->outfile_token)
	// 	{
	// 		dup2(pipe_info->fdo, STDOUT_FILENO);
	// 		close(pipe_info->fdo);
	// 		close(pipe_info->pipefd[0]);
	// 	}
	// 	else
	// 	{
	// 		dup2(cmds_list->fd[1], STDOUT_FILENO);
	// 		close(cmds_list->fd[1]);
	// 	}
	// }
	// else if (i == pipe_info->total_cmds - 1)
	// {
	// 	close(cmds_list->fd[1]);
	// 	dup2(pipe_info->fdo, STDOUT_FILENO);
	// 	close(pipe_info->fdo);
	// 	if (cmds_list->infile_token)
	// 	{
	// 		dup2(pipe_info->fdi, STDIN_FILENO);
	// 		close(pipe_info->fdi);
	// 		close(cmds_list->fd[0]);
	// 	}
	// 	else
	// 	{
	// 		dup2(cmds_list->prev->fd[0], STDIN_FILENO);
	// 		close(cmds_list->prev->fd[0]);
	// 	}
	// }
	// else
	// {
	// 	printf("Middle command\n");
	// 	if (cmds_list->infile_token)
	// 	{
	// 		dup2(pipe_info->fdi, STDIN_FILENO);
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
	printf("Hello world2\n");
}
