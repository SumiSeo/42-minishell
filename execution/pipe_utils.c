/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:29:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/21 16:09:59 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_arr_length(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	count_cmds(t_parse *cmds_list)
{
	int		total_cmd;

	total_cmd = 0;
	while (cmds_list)
	{
		if (cmds_list->cmd_array)
			total_cmd++;
		cmds_list = cmds_list->next;
	}
	return (total_cmd);
}
