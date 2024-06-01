/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:47:54 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 16:05:58 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_parse_list(t_parse	**par_list)
{
	t_parse	*nextnode;

	while (*par_list)
	{
		nextnode = (*par_list)->next;
		free(*par_list);
		(*par_list) = nextnode;
	}
}
