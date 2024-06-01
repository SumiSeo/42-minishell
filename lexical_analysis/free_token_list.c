/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:49:56 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 16:05:45 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token	**tok_list)
{
	t_token	*nextnode;

	while (*tok_list)
	{
		nextnode = (*tok_list)->next;
		free(*tok_list);
		(*tok_list) = nextnode;
	}
}