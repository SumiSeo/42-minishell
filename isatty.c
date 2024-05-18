/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:24:23 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:25:41 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main()
{
	if (isatty(STDIN_FILENO))
		printf("Standard input is a terminal.\n");
	else
		printf("Standard input is not a terminal.\n");
	if (isatty(STDOUT_FILENO))
		printf("Standard output is a terminal.\n");
	else
		printf("Standard output is not a terminal.\n");
	if (isatty(STDERR_FILENO))
		printf("Standard error is a terminal.\n");
	else
		printf("Standard error is not a terminal.\n");
	return 0;
}
