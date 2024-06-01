/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nb_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:43:16 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 16:21:26 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	count_nb_pipe(t_token *tok_list, t_data *data)
{
	int		nb;

	data->has_pipe = 0;
	nb = 0;
	while (tok_list)
	{
		if (tok_list->str[0] == '|')
			nb++;
		tok_list = tok_list->next;
	}
	data->has_pipe = nb;
}
