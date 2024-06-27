/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/27 18:10:46 by sumseo           ###   ########.fr       */
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
	data->all_paths = (char **)ft_calloc(2, sizeof(char *));
	tok_list = NULL;
	par_list = NULL;
	env_list = NULL;
	if (argc > 1)
		exit_program("Minishell does not take arguments.");
	if (argv[1] != NULL)
		exit_program("Minishell does not take arguments.");
	store_env_list(envp, &env_list);
	while (1)
	{
		disable_signal();
		if (take_input(data, env_list))
			continue ;
		if (check_input(data->input))
			continue ;
		store_path(env_list, data);
		create_token_list(data, &tok_list, env_list);
		count_nb_pipe(tok_list, data);
		get_num_token(tok_list, data);
		free(data->input);
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
		free_token_list(&tok_list);
		check_infile(par_list);
		check_outfile(par_list);
		search_command(par_list, data);
		enable_signal();
		if (data->has_pipe < 1)
		{
			exec_shell(par_list, &env_list, copy, data);
		}
		else
		{
			runtime_shell(par_list, copy, data, &env_list);
		}
		printf("HERE\n");
		// free_env_list(&env_list);
		free_parse_list(&par_list);
	}
	return (0);
}
