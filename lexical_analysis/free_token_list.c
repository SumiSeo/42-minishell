/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:49:56 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/24 16:27:27 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_list(t_token	**tok_list)
{
	t_token	*nextnode;

	while (*tok_list)
	{
		nextnode = (*tok_list)->next;
		free((*tok_list)->operator);
		free((*tok_list)->word);
		free(*tok_list);
		(*tok_list) = nextnode;
	}
}
