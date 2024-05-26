/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 18:31:30 by ftanon           ###   ########.fr       */
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
	int			i;

	i = 0;
	while (array[i])
	{
		printf("[%s]\n", array[i]);
		i++;
	}
}

void	display_parser(t_parser *begin)
{
	while (begin)
	{
		// printf("here\n");
		display_array(begin->str);
		if (begin->infile)
			printf("[%s]\n", begin->infile);
		begin = begin->next;
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

void	freestack(t_lexer	**stack_a)
{
	t_lexer	*nextnode;

	while (*stack_a)
	{
		nextnode = (*stack_a)->next;
		free(*stack_a);
		(*stack_a) = nextnode;
	}
}

int	count_lexer(t_lexer *lexer)
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

int	count_words(t_lexer *lexer)
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

void	store_lexer(t_lexer *lexer, t_parser *parser)
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
			i = count_lexer(lexer);
		if (lexer->str[0] == '>' || lexer->str[0] == '<')
		{
			lexer = lexer->next;
			len = ft_strlen(lexer->str);
			parser->infile = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(parser->infile, lexer->str, len + 1);
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
		}
	}
}

void	allocate_parser(t_lexer *lexer, t_parser **parser)
{
	int	i;
	int	k;
	t_parser	*last;

	last = *parser;
	while (last)
	{
		i = 0;
		k = 0;
		i = count_words(lexer);
		store_lexer(lexer, last);
		while (k < i)
		{
			lexer = lexer->next;
			k++;
		}
		if (lexer && lexer->str[0] == '|')
			lexer = lexer->next;
		last = last->next;
	}
}


int	main(void)
{
	char	input_string[MAXCOM];
	// char	*parsed_args[MAXLIST];
	// char	*parsed_args_piped[MAXLIST];
	int		exe_flag;
	int		piped;
	t_lexer	*lexer;
	t_parser *parser;

	// parser->str = (char **)malloc(sizeof(char *) * (3 + 1));
	lexer = NULL;
	parser = NULL;
	piped = 0;
	exe_flag = 0;
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		if (check_input(input_string))
			continue ;
		// printf("%lu\n", strlen(input_string));
		create_list(input_string, &lexer);
		display_list(lexer);
		printf("-----\n");
		create_parser(lexer, &parser);
		allocate_parser(lexer, &parser);
		display_parser(parser);
		freestack(&lexer);





		// piped = process_string(input_string, parsed_args, parsed_args_piped);
		// display_array(parsed_args);
		// if (own_cmd_handler(parsed_args))
		// 	exe_flag = 0;
		// else
		// 	exe_flag = 1 + piped;
		// if (exe_flag == 1)
		// 	exec_args(parsed_args);
		// if (exe_flag == 2)
		// 	exec_args_piped(parsed_args, parsed_args_piped);
	}
	return (0);
}

// print shell line

// take input

// process

// execflag returns zero if there is no command
// or it is a builtin command,
// 1 if it is a simple command
// 2 if it is including a pipe.

// execute

// void	create_prompt(char **env)
// {
// 	char	*prompt;

// 	(void)env;
// 	while (42)
// 	{
// 		prompt = readline(prompt);
// 	}
// }
// int	main(int argc, char **argv, char **envp)
// {
// 	if (argc != 1 || argv[1])
// 		exit_program("The program does not take arugments");

// 	create_prompt(envp);
// }