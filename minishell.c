/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/18 18:01:58 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	create_prompt(char **env)
{
	char	cur_dir[1024];
	char	*input;

	(void)env;
	while (42)
	{
		getcwd(cur_dir, 1024);
		input = readline(cur_dir);
	}
}
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
		exit_program("The program does not take arugments");

	create_prompt(envp);
}