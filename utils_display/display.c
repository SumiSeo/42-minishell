/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:01:15 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 18:08:04 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_str(char **array)
{
	int			i;

	i = 0;
	while (array[i])
	{
		printf("%s ", array[i]);
		i++;
	}
}

void	display_array(char **array)
{
	int			i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}