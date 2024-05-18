/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:55:37 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 12:57:06 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main()
{
	char	*input;

	input = readline("Enter some text: ");
	if (input)
	{
		printf("You entered: %s\n", input);
		free(input);
	}
	return (0);
}
