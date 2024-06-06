/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/06 16:14:27 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_redirection(t_parse *cmds_list, t_env *env_list,
		char **env_copy, t_data *data)
{
	(void)cmds_list;
	(void)env_list;
	(void)env_copy;
	(void)data;
	printf("Check redirection\n");
}