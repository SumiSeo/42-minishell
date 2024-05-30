/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:37:19 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 11:38:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// only handle special characters mentionned in the subject
int	check_input(char const *str)
{
	int	i;
	int	double_quotes;
	int	single_quotes;

	double_quotes = 0;
	single_quotes = 0;
	i = 0;
	if (!(str[i] >= 97 && str[i] <= 122) && str[i] != '>' && str[i] != '<')
	{
		printf("Error : Not lowercase character\n");
		return (1);
	}
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			double_quotes++;
		else if (str[i] == 39)
			single_quotes++;
		i++;
	}
	if (double_quotes > 0 && double_quotes % 2 != 0)
	{
		printf("Error : Quotes\n");
		return (1);
	}
	else if (single_quotes > 0 && single_quotes % 2 != 0)
	{
		printf("Error : Quotes\n");
		return (1);
	}
	return (0);
}