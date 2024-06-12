/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:54:51 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/10 23:57:00 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_exist(char *string)
{
	if (access(string, F_OK) == -1)
	{
		perror(string);
		return (0);
	}
	return (1);
}

int	infile_rights(char *string)
{
	if (access(string, R_OK) == -1)
	{
		perror(string);
		return (0);
	}
	return (1);
}

void	check_infile(t_parse *par_list)
{
	while (par_list)
	{
		if (par_list->infile_name != NULL
			&& ft_strlen(par_list->infile_token) == 1)
		{
			par_list->infile_exist = infile_exist(par_list->infile_name);
			if (par_list->infile_exist == 1)
				par_list->infile_access = infile_rights(par_list->infile_name);
		}
		par_list = par_list->next;
	}
}

////////////////////////////////////////////// OPEN INFILE

// void	receive_input(char *argv)
// {
// 	char	*string;
// 	int		fd1;

// 	fd1 = open("temp", O_CREAT | O_WRONLY, 0644);
// 	while (1)
// 	{
// 		string = get_next_line(0);
// 		printf("%zu\n", ft_strlen(string));
// 		if (string == NULL || ft_strncmp(string, argv, ft_strlen(string)
// 				- 1) == 0)
// 			break ;
// 		ft_putstr_fd(string, fd1);
// 		free(string);
// 	}
// }

// int	open_infile(t_parse *parser)
// {
// 	int	fd1;

// 	if (parser->infile != NULL && ft_strlen(parser->token_infile) == 2)
// 	{
// 		receive_input(parser->infile);
// 		fd1 = open("temp", O_CREAT | O_RDONLY, 0644);
// 	}
// 	else
// 	{
// 		if (parser->infile_exist == 0)
// 			fd1 = open(parser->infile, O_CREAT, 0644);
// 		else if (parser->infile_exist == 1 && parser->infile_access == 0)
// 			fd1 = open("temp", O_CREAT | O_RDONLY, 0644);
// 		else
// 			fd1 = open(parser->infile, O_RDONLY);
// 	}
// 	return (fd1);
// }

// void	open_all_infile(t_parse *parser)
// {
// 	while (parser)
// 	{
// 		if (parser->infile != NULL)
// 			parser->fd_infile = open_infile(parser);
// 		parser = parser->next;
// 	}
// }

// void	open_all_outfile(t_parse *parser)
// {
// 	while (parser)
// 	{
// 		if (parser->outfile != NULL)
// 		{
// 			if (ft_strlen(parser->token_outfile) == 2)
// 				parser->fd_outfile = open(parser->outfile,
// 						O_CREAT | O_APPEND | O_WRONLY, 0644);
// 			else
// 				parser->fd_outfile = open(parser->outfile,
// 						O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 		}
// 		parser = parser->next;
// 	}
// }