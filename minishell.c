/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/23 20:57:38 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **env)
{
	char input_string[MAXCOM];
	char *parsed_args[MAXLIST];
	char *parsed_args_piped[MAXLIST];
	int piped;
	char **copy;

	copy = env;
	(void)argv;
	piped = 0;
	if (argc > 1)
		exit_program("Minishell doe not take arguments");
	while (1)
	{
		print_dir();
		if (take_input(input_string))
			continue ;
		piped = process_string(input_string, parsed_args, parsed_args_piped);
		create_pipeline(parsed_args, *copy + 5, env);
	}
	return (0);
}