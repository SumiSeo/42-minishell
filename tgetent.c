/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tgetent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:59:05 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 16:05:38 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>   // for tgetent function
#include <stdio.h>  // for printf function
#include <stdlib.h>

int main()
{
	char *term_buffer; // Allocate a buffer to hold terminal information
	const char *term_type = "xterm"; // Example terminal type

	term_buffer = malloc(sizeof(char) * 1000);
	int result = tgetent(term_buffer, term_type);

	if (result != 1)
	{
		// Error handling if tgetent fails
		printf("Error: Unable to retrieve terminal information for type %s\n", term_type);
		return 1;
	}

	char *clr_str = tgetstr("cl", &term_buffer); // Retrieve clear screen capability
	if (clr_str != NULL)
		printf("Clear screen capability: %s\n", clr_str);
	else
		printf("Terminal capability not supported.\n");
}