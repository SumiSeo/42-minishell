/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/09 20:49:54 by sumseo           ###   ########.fr       */
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
}

void	outfile_check(t_parse *cmds_list, t_pipe *pipe_info)
{
	if (cmds_list->outfile_name)
	{
		pipe_info->outfile = open(cmds_list->outfile_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (pipe_info->outfile == -1)
			perror(cmds_list->outfile_name);
	}
}
void	redirection(t_parse *cmds_list, t_pipe *pipe_info)
{
	printf("REDIRECTION %s\n", cmds_list->cmd_array[0]);
	printf("Hello \n");
	printf("check %d\n", cmds_list->infile_exist);
	if (cmds_list->infile_exist == 1)
	{
		infile_check(cmds_list, pipe_info);
		printf("infile check");
	}
	if (cmds_list->outfile_exist == 1)
	{
		outfile_check(cmds_list, pipe_info);
		printf("outsfile check");
	}
}
