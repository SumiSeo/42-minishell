/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/11 00:12:04 by sumseo           ###   ########.fr       */
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
	else
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
	if (cmds_list->infile_exist && cmds_list->infile_name
		&& cmds_list->infile_token)
	{
		if (ft_strncmp(cmds_list->infile_token, "<<", 2) == 0)
			printf("This is heredoc\n");
		if (ft_strncmp(cmds_list->infile_token, "<", 1) == 0)
			assign_infile(cmds_list, pipe_info);
	}
	printf("Check infile or outfile ? \n");
	printf("Outfile exist ? %d\n", cmds_list->outfile_exist);
	printf("Outfile name ? %s\n", cmds_list->outfile_name);
	printf("Outfile token ? %s\n", cmds_list->outfile_token);
	printf("Outfile access ? %d\n", cmds_list->outfile_access);
	if (cmds_list->outfile_name && cmds_list->outfile_token
		&& cmds_list->outfile_access)
	{
		printf("Check outfile ? \n");
		if (ft_strncmp(cmds_list->outfile_token, ">>", 2) == 0)
			assign_outfile(cmds_list, pipe_info, 2);
		if (ft_strncmp(cmds_list->outfile_token, ">", 1) == 0)
			assign_outfile(cmds_list, pipe_info, 1);
	}
	if (cmds_list->infile_token == NULL || cmds_list->outfile_token == NULL)
		return ;
}
