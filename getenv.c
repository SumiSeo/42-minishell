/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:44:25 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:45:25 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main()
{
	// Retrieve the value of the PATH environment variable
	char *path_value = getenv("PATH");

	// Check if PATH environment variable exists
	if (path_value != NULL)
		printf("Value of PATH: %s\n", path_value);
	else
		printf("PATH environment variable not found\n");
	return (0);
}