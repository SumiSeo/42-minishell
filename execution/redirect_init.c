/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/09 20:07:28 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_check(t_parse *cmds_list, t_pipe *pipe_info)
{
	if (cmds_list->infile_name)
	{
		pipe_info->infile = open(cmds_list->infile_name, O_RDONLY);
		if (pipe_info->infile == -1)
			perror(cmds_list->infile_name);
		return (1);
	}
	return (0);
}
int	outfile_check(t_parse *cmds_list, t_pipe *pipe_info)
{
	if (cmds_list->outfile_name)
	{
		pipe_info->outfile = open(cmds_list->outfile_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (pipe_info->outfile == -1)
			perror(cmds_list->outfile_name);
		dup2(pipe_info->outfile, STDOUT_FILENO);
		return (1);
	}
	return (0);
}
void	redirection(t_parse *cmds_list, t_pipe *pipe_info)
{
	printf("REDIRECTION\n");
	if (cmds_list)
	{
		if (cmds_list->infile_exist == 1)
			infile_check(cmds_list, pipe_info);
		if (cmds_list->outfile_access == 1)
			outfile_check(cmds_list, pipe_info);
		cmds_list = cmds_list->next;
	}
}
