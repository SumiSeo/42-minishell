/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/22 17:50:37 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// function for finding pipe
// send infile to create files
int	parse_pipe(char *input_string, char **strpiped)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		// strsep is a function for extracting tokesn form strinig
		// But we are not allowed to use this function
		strpiped[i] = strsep(&input_string, "|");
		if (strpiped[i] == NULL)
			break ;
		i++;
	}
	// if there is only one command
	if (strpiped[1] == NULL)
		return (0);
	// if there are multiple commands
	else
		return (1);
}

// function for parsing command words
void	parse_space(char *str, char **parsed_args)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		parsed_args[i] = strsep(&str, " ");
		printf("%s\n", parsed_args[i]);
		if (parsed_args[i] == NULL)
			break ;
		if (strlen(parsed_args[i]) == 0)
			i--;
		i++;
	}
}

int	process_string(char *input_string, char **parsed_args,
		char **parsed_args_piped)
{
	char	*strpiped[2];
	int		piped;

	piped = 0;
	piped = parse_pipe(input_string, strpiped);
	if (piped)
	{
		parse_space(strpiped[0], parsed_args);
		parse_space(strpiped[1], parsed_args_piped);
	}
	else
	{
		parse_space(input_string, parsed_args);
	}
	return (piped);
}
