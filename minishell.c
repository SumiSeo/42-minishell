/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/22 17:58:27 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(void)
{
	char input_string[MAXCOM];
	char *parsed_args[MAXLIST];
	char *parsed_args_piped[MAXLIST];
	int exe_flag;
	int piped;

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