/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/08 18:35:56 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_check(t_parse *cmds_list)
{
	if (cmds_list->exist)
}
int	outfile_check(t_parse *cmds_list)
{
}
void	execute_redirection(t_parse *cmds_list, char **env_copy)
{
	while (cmds_list)
	{
		if (cmds_list->infile_exist)
			printf("Redirige infile\n");
		else
			printf("It does not exist");
		if (cmds_list->outfile_exist)
			printf("Redirige outfilefile\n");
		else
			printf("It does not exist");
		cmds_list = cmds_list->next;
	}
}
