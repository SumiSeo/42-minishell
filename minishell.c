/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 12:48:05 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	display(t_lexer *begin)
{
	while (begin)
	{
		printf("[%s]\n", begin->str);
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

void	display_array(char **array)
{
	int			i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}


void	push_parser(t_parser **p, int i, t_lexer *lexer)
{
	t_parser	*element;
	t_parser	*last;
	int			j;
	int			len;

	j = 0;
	last = *p;
	element = malloc(sizeof(t_lexer));
	element->str = (char **)malloc(sizeof(char *) * (i + 1));
	while (lexer && lexer->str[0] != '|')
	{
		len = ft_strlen(lexer->str);
		// printf("[%s]\n", lexer->str);
		element->str[j] = (char *)malloc(sizeof(char) * (len + 1));
		ft_strlcpy(element->str[j], lexer->str, len + 1);
		j++;
		lexer = lexer->next;	
	}
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

int	count_words(t_lexer *lexer)
{
	int		len;

	len = 0;
	if (lexer->str[0] == '"' || lexer->str[0] == 39)
	{
		len++;
		while (lexer->str[0] != '\0' && lexer->str[0] != '"' && lexer->str[0] != 39)
			len++;
		len++;
	}
	else if (lexer->str[0] == '>' && lexer->str[0] == '>')
		len = 2;
	else if (lexer->str[0] == '<' && lexer->str[0] == '<')
		len = 2;
	else if (lexer->str[0] == '|' || lexer->str[0] == '>' || lexer->str[0] == '<')
		len = 1;
	else
	{
		while (lexer->str[0] != ' ' && lexer->str[0] != '\0' && lexer->str[0] != '"' && lexer->str[0] != 39 && lexer->str[0] != '|' && lexer->str[0] != '>')
			len++;
	}
	// printf("len: %d\n", len);
	return (len);
}

// void	parsing(t_lexer *lexer, t_parser **parser)
void	create_parser(t_lexer *lexer)
{
	int	i;
	int	k;

	while (lexer)
	{
		i = 0;
		k = 0;
		i = count_words(lexer);
		printf("%d\n", i);
		while (k < i)
		{
			printf("[%s]\n", lexer->str);
			lexer = lexer->next;
			k++;
		}
		if (!lexer)
			break ;
		printf("[%s]\n", lexer->str);
		if (lexer->str[0] == '|')
			lexer = lexer->next;
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
		display(lexer);
		// test(&parser);
		// parsing(lexer, &parser);
		// display_array(parser->str);
		// create_parser(lexer);
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