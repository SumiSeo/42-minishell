/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/30 17:36:11 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	display_list(t_lexer *begin)
{
	while (begin)
	{
		printf("[%s]\n", begin->str);
		begin = begin->next;
	}
}

void	display_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s ", array[i]);
		i++;
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
		printf("token infile : %s\n", begin->token_infile);
		printf("infile : %s\n", begin->infile);
		printf("commande : ");
		display_array(begin->str);
		printf("\n");
		printf("token outfile : %s\n", begin->token_outfile);
		printf("outfile : %s\n", begin->outfile);
		printf("builtin : %s\n", begin->builtin);
		printf("fd_infile : %d\n", begin->fd_infile);
		printf("fd_outfile : %d\n", begin->fd_outfile);
		begin = begin->next;
		i++;
	}
}

void	display_list_num(t_parser *begin)
{
	while (begin)
	{
		printf("[%d]\n", begin->index);
		begin = begin->next;
	}
}

void	freestack(t_lexer **stack_a)
{
	t_lexer	*nextnode;

	while (*stack_a)
	{
		nextnode = (*stack_a)->next;
		free(*stack_a);
		(*stack_a) = nextnode;
	}
}

void	free_parser(t_parser **stack_a)
{
	t_parser	*nextnode;

	while (*stack_a)
	{
		nextnode = (*stack_a)->next;
		free(*stack_a);
		(*stack_a) = nextnode;
	}
}

int	count_lexer(t_lexer *lexer)
{
	int	len;

	len = 0;
	while (lexer && lexer->str[0] != '|' && lexer->str[0] != '>'
		&& lexer->str[0] != '<')
	{
		len++;
		lexer = lexer->next;
	}
	return (len);
}

int	count_words(t_lexer *lexer)
{
	int	len;

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

void	store_lexer(t_lexer *lexer, t_parser *parser)
{
	int	i;
	int	k;
	int	j;
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
			i = count_lexer(lexer);
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
			while (lexer && lexer->str[0] != '|' && lexer->str[0] != '>'
				&& lexer->str[0] != '<')
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

void	allocate_parser(t_lexer *lexer, t_parser *parser)
{
	int	i;
	int	k;

	while (parser)
	{
		i = 0;
		k = 0;
		i = count_words(lexer);
		store_lexer(lexer, parser);
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

void	create_parser(t_lexer *lexer, t_parser **parser)
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
		i = count_words(lexer);
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

int	main(int argc, char **argv, char **env)
{
	char input_string[MAXCOM];
	// char *parsed_args[MAXLIST];
	// char *parsed_args_piped[MAXLIST];
	char **copy;
	copy = env;
	(void)env;
	(void)argv;
	int piped;
	t_lexer *lexer;
	t_parser *parser;

	// parser->str = (char **)malloc(sizeof(char *) * (3 + 1));
	lexer = NULL;
	parser = NULL;
	piped = 0;
	if (argc > 1)
		exit_program("Minishell doe not take arguments.");
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		if (check_input(input_string))
			continue ;
		create_list(input_string, &lexer);
		// display_list(lexer);
		printf("-----\n");
		create_parser(lexer, &parser);
		allocate_parser(lexer, parser);
		display_parser(parser);

		// piped = process_string(input_string, parsed_args, parsed_args_piped);
		// display_array(parsed_args);
		// if (own_cmd_handler(parsed_args))
		// 	exe_flag = 0;
		// else
		// 	exe_flag = 1 + piped;
		// if (exe_flag == 1)
		// 	exec_args(parsed_args);
		// if (exe_flag == 2)

		// exec_args_piped(parsed_args, parsed_args_piped);
		// piped = process_string(input_string, parsed_args, parsed_args_piped);
		// printf("parser %c\n", *parser->str[2]);

		if (!is_builtin(parser))
			continue ;
		// else
		// {
		// 	if (piped == 1)
		// 		runtime_shell(&parser);
		// 	else
		// 		exec_shell(&parser, copy);
		// }
		freestack(&lexer);
		free_parser(&parser);
	}
	return (0);
}