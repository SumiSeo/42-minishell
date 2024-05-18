/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:45:46 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/18 17:26:02 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	create_prompt(char **env)
{
	char	*prompt;

	(void)env;
	while (42)
	{
		prompt = readline(prompt);
	}
}
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv[1])
		exit_program("The program does not take arugments");

	create_prompt(envp);
}