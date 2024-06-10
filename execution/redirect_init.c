/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/10 16:57:57 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	assign_infile(t_parse *cmds_list, t_pipe *pipe_info)
{
	printf("*****Infile assigned\n ");
	if (cmds_list->infile_name)
	{
		pipe_info->infile = open(cmds_list->infile_name, O_RDONLY);
		if (pipe_info->infile == -1)
			perror(cmds_list->infile_name);
	}
	return ;
}

void	assign_outfile(t_parse *cmds_list, t_pipe *pipe_info, int flag)
{
	if (flag == 1)
	{
		printf("*****Outfile newly created\n ");
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
		printf("*****Outfile appended\n ");
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
	if (cmds_list->infile_token)
	{
		if (ft_strncmp(cmds_list->infile_token, "<", 1) == 0)
			assign_infile(cmds_list, pipe_info);
		if (ft_strncmp(cmds_list->infile_token, "<<", 2) == 0)
			printf("This is heredoc\n");
	}
	if (ft_strncmp(cmds_list->outfile_token, ">>", 2) == 0)
		assign_outfile(cmds_list, pipe_info, 2);
	else if (ft_strncmp(cmds_list->outfile_token, ">", 1) == 0)
		assign_outfile(cmds_list, pipe_info, 1);
}
