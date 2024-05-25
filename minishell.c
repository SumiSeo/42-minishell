/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/25 15:20:59 by sumseo           ###   ########.fr       */
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

	(void)argv;
	copy = env;

	if (argc > 1)
		exit_program("Minishell doe not take arguments.");
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		process_string(input_string, parsed_args, parsed_args_piped);

		// execute_cmds(parsed_args, env);
		execute_pipeline(parsed_args_piped, *copy + 5, env);
	}
	return (0);
}