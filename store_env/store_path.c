/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:41:01 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 16:09:54 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_path(t_env *env_list, t_data *data)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->str, "PATH", 4) == 0)
		{
			data->str = ft_split(env_list->str + 5, ':');
			break ;
		}
		env_list = env_list->next;
	}
}

void	display_path(t_data *data)
{
	display_array(data->str);
	printf("nb pipes : %d\n", data->has_pipe);
}