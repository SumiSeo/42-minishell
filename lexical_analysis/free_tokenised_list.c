/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tockenised_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:49:56 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 11:49:58 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokenised_list(t_lexer	**stack_a)
{
	t_lexer	*nextnode;

	while (*stack_a)
	{
		nextnode = (*stack_a)->next;
		free(*stack_a);
		(*stack_a) = nextnode;
	}
}