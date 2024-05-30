/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsed_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:47:54 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 11:48:10 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_parsed_list(t_parser	**stack_a)
{
	t_parser	*nextnode;

	while (*stack_a)
	{
		nextnode = (*stack_a)->next;
		free(*stack_a);
		(*stack_a) = nextnode;
	}
}
