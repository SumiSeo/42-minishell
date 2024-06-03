/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/03 18:53:45 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	parse(t_data *data)
{
	// int	i;
	// int len;
	// i = 0;
	// len = 0;
	int	start;
	int end;

	start = 0;
	end = ft_strlen(data->input_string);
	if (data->input_string[0] == '"' && data->input_string[1] == '"')
	{
		start = start + 2;
		end = end - 2;
	}
	while (start < end)
	{
		printf("%c", data->input_string[start]);
		start++;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_token *tok_list;
	t_parse *par_list;
	t_env *env_list;
	t_data *data;

	// int builtin_check;

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
		if (take_input(data))
			continue ;
		parse(data);
		// if (check_input(data->input_string))
		// 	continue ;
		// store_path(env_list, data);
		// create_token_list(data->input_string, &tok_list);
		// count_nb_pipe(tok_list, data);
		// create_parse_list(tok_list, &par_list);
		// store_command(tok_list, par_list);
		// check_infile(par_list);
		// check_outfile(par_list);
		// search_command(par_list, data);
		// printf("-----\n");
		// display_path(data);
		// printf("-----\n");
		// display_token_list(tok_list);
		// printf("-----\n");
		// display_parse_list(par_list);

		// if (is_builtin(par_list, env_list))
		// 	builtin_check = 1;
		// if (!builtin_check)
		// {
		// 	exec_shell(par_list, env_list);
		// }
		// free
		
		free_token_list(&tok_list);
		free_parse_list(&par_list);
	}
	return (0);
}