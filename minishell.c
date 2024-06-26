/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/26 16:47:41 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*tok_list;
	t_parse	*par_list;
	t_env	*env_list;
	t_data	*data;
	int		builtin_check;
	char	**copy;

	copy = envp;
	builtin_check = 0;
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
		disable_signal();
		if (take_input(data, env_list))
			continue ;
		if (check_input(data->input))
			continue ;
		store_path(env_list, data);
		create_token_list(data, &tok_list, env_list);
		count_nb_pipe(tok_list, data);
		get_num_token(tok_list, data);
		if (check_bracket_dup(tok_list))
		{
			free_token_list(&tok_list);
			continue ;
		}
		if (check_bracket_error(tok_list, data))
		{
			free_token_list(&tok_list);
			continue ;
		}
		create_parse_list(tok_list, &par_list);
		store_command(tok_list, par_list);
		check_infile(par_list);
		check_outfile(par_list);
		search_command(par_list, data);
		// printf("-----\n");
		// // display_path(data);
		// printf("-----\n");
		// display_token_list(tok_list);
		// printf("-----\n");
		// display_parse_list(par_list);
		// // test(par_list);
		printf("-----TRUE MINISHELL-----\n");
		if (data->has_pipe < 1)
			exec_shell(par_list, env_list, copy);
		else
		{
			enable_signal();
			runtime_shell(par_list, copy, data, env_list);
		}
		free(data->input);
		free_array(data->all_paths);
		free_token_list(&tok_list);
		free_parse_list(&par_list);
	}
	return (0);
}
