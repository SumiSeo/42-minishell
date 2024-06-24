/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:47:54 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/24 17:22:31 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_parse_list(t_parse	**par_list)
{
	t_parse	*nextnode;

	while (*par_list)
	{
		nextnode = (*par_list)->next;
		free((*par_list)->infile_token);
		free((*par_list)->infile_name);
		free((*par_list)->outfile_token);
		free((*par_list)->outfile_name);
		free_array((*par_list)->cmd_array);
		free((*par_list)->path);
		free(*par_list);
		(*par_list) = nextnode;
	}
}
