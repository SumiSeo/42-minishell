/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/08 22:19:35 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_check(t_parse *cmds_list)
{
	int	infile;

	if (cmds_list->infile_name)
	{
		infile = open(cmds_list->infile_name, O_RDONLY);
		if (infile == -1)
			perror(cmds_list->infile_name);
	}
	return (1);
}
int	outfile_check(t_parse *cmds_list)
{
	int	outfile;

	printf("Outfile \n");
	if (cmds_list->outfile_name)
	{
		outfile = open(cmds_list->outfile_name, O_WRONLY | O_TRUNC | O_CREAT,
				0777);
		if (outfile == -1)
			perror(cmds_list->outfile_name);
		return (1);
	}
}
void	redirection(t_parse *cmds_list)
{
	printf("REDIRECTION\n");
	while (cmds_list)
	{
		if (cmds_list->infile_exist == 1)
			infile_check(cmds_list);
		if (cmds_list->outfile_access == 1)
			outfile_check(cmds_list);
		cmds_list = cmds_list->next;
	}
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
}
