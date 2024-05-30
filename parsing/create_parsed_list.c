/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:43:11 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 12:12:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_parser(t_parser *begin)
{
	int	i;

	i = 0;
	while (begin)
	{
		printf("\n");
		printf("Commande %d\n", i);
		printf("infile : %s\n", begin->token_infile);
		printf("infile : %s\n", begin->infile);
		printf("commande : ");
		display_array(begin->str);
		printf("\n");
		printf("outfile : %s\n", begin->token_outfile);
		printf("outfile : %s\n", begin->outfile);
		printf("builtin : %s\n", begin->builtin);
		printf("fd_infile : %d\n", begin->fd_infile);
		printf("fd_outfile : %d\n", begin->fd_outfile);
		begin = begin->next;
		i++;
	}
}

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
	element->builtin = NULL;
	element->fd_infile = 0;
	element->fd_outfile = 0;
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
