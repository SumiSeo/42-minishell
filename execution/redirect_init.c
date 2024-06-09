/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/09 22:20:30 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	infile_check(t_parse *cmds_list, t_pipe *pipe_info)
{
	if (cmds_list->infile_name)
	{
		pipe_info->infile = open(cmds_list->infile_name, O_RDONLY);
		if (pipe_info->infile == -1)
			perror(cmds_list->infile_name);
	}
	return ;
}

void	outfile_check(t_parse *cmds_list, t_pipe *pipe_info, int flag)
{
	if (flag == 1)
	{
		if (cmds_list->outfile_name)
		{
			pipe_info->outfile = open(cmds_list->outfile_name,
					O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (pipe_info->outfile == -1)
				perror(cmds_list->outfile_name);
		}
	}
	if (flag == 2)
	{
		if (cmds_list->outfile_name)
		{
			pipe_info->outfile = open(cmds_list->outfile_name,
					O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (pipe_info->outfile == -1)
				perror(cmds_list->outfile_name);
		}
	}
	return ;
}
void	redirection(t_parse *cmds_list, t_pipe *pipe_info)
{
	printf("REDIRECTION %s\n", cmds_list->cmd_array[0]);
	if (cmds_list->infile_exist)
	{
		infile_check(cmds_list, pipe_info);
	}
	if (cmds_list->outfile_access)
	{
		outfile_check(cmds_list, pipe_info, 1);
	}
	// if (ft_strncmp(cmds_list->infile_token, "<", 2) == 0)
	// 	infile_check(cmds_list, pipe_info);
	// else if (ft_strncmp(cmds_list->infile_token, "<<", 3) == 0)
	// 	printf("This is only heredoc checker\n");
	// if (ft_strncmp(cmds_list->outfile_token, ">", 2) == 0)
	// 	outfile_check(cmds_list, pipe_info, 1);
	// else if (ft_strncmp(cmds_list->outfile_token, ">>", 3) == 0)
	// 	outfile_check(cmds_list, pipe_info, 2);
}
