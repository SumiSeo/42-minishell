/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioctl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:44:35 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:44:39 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

int main()
{
	struct winsize w;
	int result;

	// Use STDOUT_FILENO to refer to the file descriptor of the standard output
	result = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (result == -1)
	{
		perror("ioctl");
		return 1;
	}
	printf("Columns: %d\n", w.ws_col);
	printf("Rows: %d\n", w.ws_row);
	return 0;
}