/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/25 13:02:33 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	display(t_list *begin)
{
	while (begin)
	{
		printf("[%s]\n", begin->str);
		begin = begin->next;
	}
}

void	freestack(t_list	**stack_a)
{
	t_list	*nextnode;

	while (*stack_a)
	{
		nextnode = (*stack_a)->next;
		free(*stack_a);
		(*stack_a) = nextnode;
	}
}

int	main(void)
{
	char	input_string[MAXCOM];
	// char	*parsed_args[MAXLIST];
	// char	*parsed_args_piped[MAXLIST];
	int		exe_flag;
	int		piped;
	t_list	*lexer;

	lexer = NULL;
	piped = 0;
	exe_flag = 0;
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		// if (check_input(input_string))
		// 	continue ;
		// printf("%lu\n", strlen(input_string));
		create_list(input_string, ' ', &lexer);
		display(lexer);
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