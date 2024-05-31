/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/31 17:24:55 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	input_string[MAXCOM];
	// char	*parsed_args[MAXLIST];
	// char	*parsed_args_piped[MAXLIST];
	// int		exe_flag;
	int		piped;
	t_lexer		*lexer;
	t_parser	*parser;
	t_envp		*env;
	t_env		*path;


	path =  malloc(sizeof(t_env));
	// parser->str = (char **)malloc(sizeof(char *) * (3 + 1));
	lexer = NULL;
	parser = NULL;
	env = NULL;
	piped = 0;
	if (argc > 1)
		exit_program("Minishell doe not take arguments.");
	if (argv[1] != NULL)
		exit_program("Minishell doe not take arguments.");
	store_env(envp, &env);

	while (1)
	{
		// print_dir();
		if (take_input(input_string))
			continue ;
		if (check_input(input_string))
			continue ;
		// printf("%lu\n", strlen(input_string));
		store_path(env, path);
		// display_array(path->str);
		create_tokenized_list(input_string, &lexer);
		display_lexer(lexer);
		printf("-----\n");
		create_parsed_list(lexer, &parser);
		store_command(lexer, parser);
		// display_array(parser->paths_array);
		check_infile(parser);
		check_outfile(parser);
		search_command(parser, path);

		display_parser(parser);
		// display_env(env);
		free_tokenised_list(&lexer);
		free_parsed_list(&parser);

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