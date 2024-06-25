/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:15:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/24 19:20:51 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_heredoc(t_parse *cmds_list)
{
	int tmp = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	char *str;
	while (1)
	{
		str = readline(">");
		if (str == NULL)
		{
			printf("warning: here-document delimited by end-of-file (wanted `%s')\n",
				cmds_list->delimiter);
			break ;
		}
		if (ft_strncmp(str, cmds_list->delimiter,
				ft_strlen(cmds_list->delimiter)) == 0)
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, tmp);
		ft_putstr_fd("\n", tmp);
		free(str);
	}
	close(tmp);
	open("tmp", O_RDONLY, 0644);
	cmds_list->infile = tmp;
}