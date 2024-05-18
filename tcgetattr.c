/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcgetattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:52:42 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:54:09 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	struct termios term;

	if(tcgetattr(STDIN_FILENO, &term) == -1)
	{
    	perror("tcgetattr");
    	exit(EXIT_FAILURE);
	}
	printf("c_iflag: %lx\n", (unsigned long) term.c_iflag);
	printf("c_oflag: %lx\n", (unsigned long) term.c_oflag);
	printf("c_cflag: %lx\n", (unsigned long) term.c_cflag);
	printf("c_lflag: %lx\n", (unsigned long) term.c_lflag);
	if(tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}