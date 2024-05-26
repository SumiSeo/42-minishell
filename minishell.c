/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/26 17:27:19 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	// t_pipe *pipeline;
	char input_string[MAXCOM];
	char *parsed_args[MAXLIST];
	char *parsed_args_piped[MAXLIST];
	char **copy;
	int piped;

	(void)argv;
	copy = env;
	while (*copy)
	{
		if (ft_strncmp(*copy, "PATH=", 5) == 0)
			break ;
		copy++;
	}
	piped = 0;
	if (argc > 1)
		exit_program("Minishell doe not take arguments.");
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		piped = process_string(input_string, parsed_args, parsed_args_piped);
		if (is_builtin(parsed_args))
			continue ;
		else
		{
			if (piped == 1)
				runtime_shell(parsed_args, parsed_args_piped);
			else
				exec_shell(parsed_args, *copy, env);
		}
	}
	return (0);
}