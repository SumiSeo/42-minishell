/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_current_directory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:02:51 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/23 19:47:23 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Function to print Current Directory.
void	print_dir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("\nCurrent Dir: %s", cwd);
}
