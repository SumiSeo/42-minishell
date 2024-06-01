/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/01 16:05:15 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			input_string[MAXCOM];
	t_token			*tok_list;
	t_parse			*par_list;
	t_env			*env_list;
	t_data			*data;
	// int		exe_flag;

	data = malloc(sizeof(t_data));
	tok_list = NULL;
	par_list = NULL;
	env_list = NULL;
	if (argc > 1)
		exit_program("Minishell doe not take arguments.");
	if (argv[1] != NULL)
		exit_program("Minishell doe not take arguments.");
	store_env_list(envp, &env_list);
	while (1)
	{
		// print_dir();
		if (take_input(input_string))
			continue ;
		if (check_input(input_string))
			continue ;
		store_path(env_list, data);
		create_token_list(input_string, &tok_list);
		count_nb_pipe(tok_list, data);
		create_parse_list(tok_list, &par_list);
		store_command(tok_list, par_list);
		check_infile(par_list);
		check_outfile(par_list);
		search_command(par_list, data);
		// printf
		printf("-----\n");
		display_path(data);
		printf("-----\n");
		display_token_list(tok_list);
		printf("-----\n");
		display_parse_list(par_list);
		// free
		free_token_list(&tok_list);
		free_parse_list(&par_list);

	// 	// piped = process_string(input_string, parsed_args, parsed_args_piped);
	// 	// display_array(parsed_args);
	// 	// if (own_cmd_handler(parsed_args))
	// 	// 	exe_flag = 0;
	// 	// else
	// 	// 	exe_flag = 1 + piped;
	// 	// if (exe_flag == 1)
	// 	// 	exec_args(parsed_args);
	// 	// if (exe_flag == 2)
	// 	// 	exec_args_piped(parsed_args, parsed_args_piped);
	// 	// piped = process_string(input_string, parsed_args, parsed_args_piped);
	// 	// if (is_builtin(parsed_args))
	// 	// 	continue ;
	// 	// else
	// 	// {
	// 	// 	if (piped == 1)
	// 	// 		runtime_shell(parsed_args, parsed_args_piped);
	// 	// 	else
	// 	// 		exec_shell(parsed_args, *copy, env);
	// 	// }
	}
	return (0);
}