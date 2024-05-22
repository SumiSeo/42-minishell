/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_store_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:59:39 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/20 12:53:58 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Function to take input 
int	take_input(char *str)
{
	char	*buf;

	buf = readline("\n>>> ");
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return (0);
	}
	else
		return (1);
}
