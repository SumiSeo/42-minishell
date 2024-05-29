/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_store_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:59:39 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/25 21:07:34 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Function to take input
int	take_input(char *str)
{
	char	*buf;

	buf = readline("💪");
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return (0);
	}
	else
		return (1);
}
