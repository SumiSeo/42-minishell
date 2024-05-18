/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcsetattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:48:24 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:48:58 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main()
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &term); // Get current attributes
	// Modify the attributes
	term.c_lflag &= ~(ICANON | ECHO); // Turn off canonical mode and echoing
	term.c_cc[VMIN] = 1; // Minimum number of characters to read
	term.c_cc[VTIME] = 0; // Timeout for read (0 = no timeout)
	// Set the modified attributes
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
	{
		perror("tcsetattr");
		return 1;
	}
	// Now you can read input character by character
	char c;
	while (1)
	{
		read(STDIN_FILENO, &c, 1);
		printf("You entered: %c\n", c);
	}
	return 0;
}
