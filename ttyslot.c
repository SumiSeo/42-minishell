/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttyslot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:35:21 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:36:00 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main() {
	int slot;

	// Get the slot number of the current terminal
	slot = ttyslot();
	// Check if ttyslot returned a valid slot
	if (slot == 0)
		printf("Could not find the slot number for the terminal.\n");
	else
		printf("The slot number for the terminal is: %d\n", slot);
	return (0);
}
