/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttyname.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:29:49 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:32:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main() {
	int fd = 0;
	char *terminal_name;

	terminal_name = ttyname(fd);
	if (terminal_name)
		printf("The terminal associated with file descriptor %d is: %s\n", fd, terminal_name);
	else
		perror("ttyname");
	return (0);
}