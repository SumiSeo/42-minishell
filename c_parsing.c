/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/20 12:51:44 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Help command builtin 
void	open_help(void)
{
	puts("\n***WELCOME TO MY SHELL HELP***"
		"\nCopyright @ Suprotik Dey"
		"\n-Use the shell at your own risk..."
		"\nList of Commands supported:"
		"\n>cd"
		"\n>ls"
		"\n>exit"
		"\n>all other general commands available in UNIX shell"
		"\n>pipe handling"
		"\n>improper space handling");

	return ;
}

// Function to execute builtin commands 
int	own_cmd_handler(char **parsed)
{
	int		no_of_own_cmds;
	int		i;
	int		switch_own_arg;
	char	*list_of_own_cmds[4];
	char	*username;

	no_of_own_cmds = 4;
	switch_own_arg = 0;
	i = 0;
	list_of_own_cmds[0] = "exit";
	list_of_own_cmds[1] = "cd";
	list_of_own_cmds[2] = "help";
	list_of_own_cmds[3] = "hello";

	while (i < no_of_own_cmds)
	{
		if (strcmp(parsed[0], list_of_own_cmds[i]) == 0)
		{
			switch_own_arg = i + 1;
			break ;
		}
		i++;
	}
	if (switch_own_arg == 1)
	{
		printf("\nGoodbye\n");
		exit(0);
	}
	else if (switch_own_arg == 2)
	{
		chdir(parsed[1]);
		return (1);
	}
	else if (switch_own_arg == 3)
	{
		open_help();
		return (1);
	}
	else if (switch_own_arg == 4)
	{
		username = getenv("USER");
		printf("\nHello %s.\n", username);
		return (1);
	}
	return (0);
}

// function for finding pipe 
int	parse_pipe(char	*str, char	**strpiped)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break ;
		i++;
	}
	if (strpiped[1] == NULL)
		return (0);
	else
		return (1);
}

// function for parsing command words 
void	parse_space(char *str, char **parsed)
{
	int	i;

	i = 0;
	while (i < MAXLIST)
	{
		parsed[i] = strsep(&str, " ");
		printf("%s\n", parsed[i]);
		if (parsed[i] == NULL)
			break ;
		if (strlen(parsed[i]) == 0)
			i--;
		i++;
	}
}

int	process_string(char	*str, char	**parsed, char	**parsedpipe)
{
	char	*strpiped[2];
	int		piped;

	piped = 0;
	piped = parse_pipe(str, strpiped);
	if (piped)
	{
		parse_space(strpiped[0], parsed);
		parse_space(strpiped[1], parsedpipe);
	}
	else
	{
		parse_space(str, parsed);
	}
	if (own_cmd_handler(parsed))
		return (0);
	else
		return (1 + piped);
}
