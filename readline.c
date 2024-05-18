/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:55:37 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 14:21:10 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#define HISTORY_FILE "history_file"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("Enter some text (or 'exit' to quit): ");
		if (input)
		{
			if (strcmp(input, "exit") == 0)
			{
				free(input);
				break ;
			}
			add_history(input);
			printf("You entered: %s\n", input);
			free(input);
		}
	}
	return (0);
}

// int	main()
// {
// 	char	*input;

// 	input = readline("Enter some text: ");
// 	if (input)
// 	{
// 		printf("You entered: %s\n", input);
// 		free(input);
// 	}
// 	return (0);
// }
