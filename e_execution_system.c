/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_execution_system.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:11:46 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/23 18:59:35 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Function where the system command is executed
// only one command (ex) : ls
void	exec_args(char **parsed)
{
	pid_t	pid;

	printf("only one command");
	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return ;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
			printf("\nCould not execute command..");
		exit(0);
	}
	else
	{
		wait(NULL);
		return ;
	}
}

// Function where the piped system commands is executed
// only two commands (ex) : ls | cat
void	exec_args_piped(char **parsed, char **parsedpipe)
{
	int		pipefd[2];
	pid_t	p1;
	pid_t	p2;

	if (pipe(pipefd) < 0)
	{
		printf("\nPipe could not be initialized");
		return ;
	}
	p1 = fork();
	if (p1 < 0)
	{
		printf("\nCould not fork");
		return ;
	}
	if (p1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command 1..");
			exit(0);
		}
	}
	else
	{
		p2 = fork();
		if (p2 < 0)
		{
			printf("\nCould not fork");
			return ;
		}
		if (p2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0)
			{
				printf("\nCould not execute command 2..");
				exit(0);
			}
		}
		else
		{
			wait(NULL);
			wait(NULL);
		}
	}
}
