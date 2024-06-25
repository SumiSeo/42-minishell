/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:56:34 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/25 18:59:16 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pid_array(t_pipe *pipe_info)
{
	pipe_info->counter = 0;
	pipe_info->pids = ft_calloc(pipe_info->total_cmds + 1, sizeof(pid_t));
}

void	store_pid(t_pipe *pipe_info, pid_t fork_id)
{
	pipe_info->pids[pipe_info->counter] = fork_id;
	pipe_info->counter++;
}

