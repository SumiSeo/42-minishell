/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/20 15:28:42 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(void)
{
	char	input_string[MAXCOM];
	char	*parsed_args[MAXLIST];
	char	*parsed_args_piped[MAXLIST];
	int		exe_flag;
	int		piped;

	piped = 0;
	exe_flag = 0;
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		piped = process_string(input_string, parsed_args, parsed_args_piped);
		if (own_cmd_handler(parsed_args))
			exe_flag = 0;
		else
			exe_flag = 1 + piped;
		if (exe_flag == 1)
			exec_args(parsed_args);
		if (exe_flag == 2)
			exec_args_piped(parsed_args, parsed_args_piped);
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