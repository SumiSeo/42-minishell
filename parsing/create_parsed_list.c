/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parsed_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:43:11 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 17:44:39 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_operator(t_lexer *lexer)
{
	int		len;

	len = 0;
	while (lexer && lexer->str[0] != '|' && lexer->str[0] != '>' && lexer->str[0] != '<')
	{
		len++;
		lexer = lexer->next;
	}
	return (len);
}

int	count_words_pipe(t_lexer *lexer)
{
	int		len;

	len = 0;
	while (lexer && lexer->str[0] != '|')
	{
		len++;
		lexer = lexer->next;
	}
	return (len);
}

void	push_parser(t_parser **p, int i)
{
	t_parser	*element;
	t_parser	*last;

	last = *p;
	element = malloc(sizeof(t_parser));
	element->index = i;
	element->infile = NULL;
	element->outfile = NULL;
	element->token_infile = NULL;
	element->token_outfile = NULL;
	element->infile_exist = 0;
	element->infile_access = 0;
	element->outfile_exist = 0;
	element->outfile_access = 0;
	element->has_here_doc = 0;
	element->builtin = NULL;
	element->infile = NULL;
	element->next = NULL;
	if (*p == NULL)
	{
		*p = element;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

void	split_command(t_lexer *lexer, t_parser *parser)
{
	int	i;
	int	k;
	int j;
	int	len;

	len = 0;
	j = 0;
	while (lexer && lexer->str[0] != '|')
	{
		i = 0;
		k = 0;
		if (lexer->str[0] == '>' || lexer->str[0] == '<')
			i = 2;
		else
			i = count_words_operator(lexer);
		if (lexer->str[0] == '<')
		{
			len = ft_strlen(lexer->str);
			parser->token_infile = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(parser->token_infile, lexer->str, len + 1);
			lexer = lexer->next;
			len = ft_strlen(lexer->str);
			parser->infile = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(parser->infile, lexer->str, len + 1);
			lexer = lexer->next;
		}
		else if (lexer->str[0] == '>')
		{
			len = ft_strlen(lexer->str);
			parser->token_outfile = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(parser->token_outfile, lexer->str, len + 1);
			lexer = lexer->next;
			len = ft_strlen(lexer->str);
			parser->outfile = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(parser->outfile, lexer->str, len + 1);
			lexer = lexer->next;
		}
		else
		{
			parser->str = (char **)malloc(sizeof(char *) * (i + 1));
			while (lexer && lexer->str[0] != '|' && lexer->str[0] != '>' && lexer->str[0] != '<')
			{
				len = ft_strlen(lexer->str);
				parser->str[j] = (char *)malloc(sizeof(char) * (len + 1));
				ft_strlcpy(parser->str[j], lexer->str, len + 1);
				j++;
				lexer = lexer->next;
			}
			parser->str[j] = NULL;
		}
	}
}

void	store_command(t_lexer *lexer, t_parser *parser)
{
	int	i;
	int	k;

	while (parser)
	{
		i = 0;
		k = 0;
		i = count_words_pipe(lexer);
		split_command(lexer, parser);
		while (k < i)
		{
			lexer = lexer->next;
			k++;
		}
		if (lexer && lexer->str[0] == '|')
			lexer = lexer->next;
		parser = parser->next;
	}
}

void	create_parsed_list(t_lexer *lexer, t_parser **parser)
{
	int	i;
	int	k;
	int	index;

	index = 0;
	while (lexer)
	{
		index++;
		i = 0;
		k = 0;
		i = count_words_pipe(lexer);
		push_parser(parser, index);
		while (k < i)
		{
			lexer = lexer->next;
			k++;
		}
		if (lexer && lexer->str[0] == '|')
			lexer = lexer->next;
	}
}

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

void	check_infile(t_parser *parser)
{
	while(parser)
	{
		if (parser->infile != NULL && ft_strlen(parser->token_infile) == 1)
		{
			parser->infile_exist = infile_exist(parser->infile);
			if (parser->infile_exist == 1)
				parser->infile_access = infile_rights(parser->infile);
		}
		parser = parser->next;
	}
}

int	outfile_exist(char *string)
{
	if (access(string, F_OK) == -1)
	{
		perror(string);
		return (0);
	}
	return (1);
}

void	check_outfile(t_parser *parser)
{
	while(parser)
	{
		if (parser->outfile != NULL)
		{
			parser->outfile_exist = outfile_exist(parser->outfile);
			if (parser->outfile_exist == 1 && access(parser->outfile, W_OK) == -1)
				parser->outfile_access = 0;
			else
				parser->outfile_access = 1;
		}
		parser = parser->next;
	}
}

void	display_parser(t_parser *begin)
{
	int	i;

	i = 0;
	while (begin)
	{
		printf("\n");
		printf("Commande %d\n", i);
		printf("infile_token : %s\n", begin->token_infile);
		printf("infile : %s\n", begin->infile);
		printf("infile exist : %d\n", begin->infile_exist);
		printf("infile access : %d\n", begin->infile_access);
		printf("commande : ");
		display_str(begin->str);
		printf("\n");
		printf("outfile_token : %s\n", begin->token_outfile);
		printf("outfile : %s\n", begin->outfile);
		printf("outfile exist : %d\n", begin->outfile_exist);
		printf("outfile access : %d\n", begin->outfile_access);
		printf("builtin : %s\n", begin->builtin);
		begin = begin->next;
		i++;
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
// 		if (string == NULL
// 			|| ft_strncmp(string, argv, ft_strlen(string) - 1) == 0)
// 			break ;
// 		ft_putstr_fd(string, fd1);
// 		free(string);
// 	}
// }

// int	open_infile(t_parser *parser)
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

// void		open_all_infile(t_parser *parser)
// {
// 	while(parser)
// 	{
// 		if (parser->infile != NULL)
// 			parser->fd_infile = open_infile(parser);
// 		parser = parser->next;
// 	}
// }

// void		open_all_outfile(t_parser *parser)
// {
// 	while(parser)
// 	{
// 		if (parser->outfile != NULL)
// 		{
// 			if (ft_strlen(parser->token_outfile) == 2)
// 				parser->fd_outfile = open(parser->outfile, O_CREAT | O_APPEND | O_WRONLY, 0644);
// 			else
// 				parser->fd_outfile = open(parser->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 		}
// 		parser = parser->next;
// 	}
// }