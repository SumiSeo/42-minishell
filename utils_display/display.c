/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:01:15 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 12:01:27 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_list(t_lexer *begin)
{
	while (begin)
	{
		printf("[%s]\n", begin->str);
		begin = begin->next;
	}
}

void	display_array(char **array)
{
	int			i;

	i = 0;
	while (array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
}