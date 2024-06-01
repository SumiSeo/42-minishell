/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:55:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 16:21:13 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	outfile_exist(char *string)
{
	if (access(string, F_OK) == -1)
	{
		perror(string);
		return (0);
	}
	return (1);
}

void	check_outfile(t_parse *par_list)
{
	while (par_list)
	{
		if (par_list->outfile_name != NULL)
		{
			par_list->outfile_exist = outfile_exist(par_list->outfile_name);
			if (par_list->outfile_exist == 1 && access(par_list->outfile_name, W_OK) == -1)
				par_list->outfile_access = 0;
			else
				par_list->outfile_access = 1;
		}
		par_list = par_list->next;
	}
}