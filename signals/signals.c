/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:19:25 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/22 18:44:58 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_not_blocking(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// print_dir();
	}
}

void	sigint_blocking_cmd(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
	}
}

void	sigquit(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_putchar_fd('\n', 1);
		// rl_replace_line("", 0);
		// rl_on_new_line();
	}
}

void	disable_signal(void)
{
	// printf("disable\n");
	signal(SIGINT, sigint_not_blocking);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	enable_signal(void)
{
	// printf("enable\n");
	signal(SIGINT, sigint_blocking_cmd);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, sigquit);
	signal(SIGTSTP, SIG_DFL);
}

void handle_ctrld(t_parse *par_list)
{
	int		fd[2];
	pid_t	pid;
	char	*buffer;

	buffer = malloc(sizeof(char) * 10);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve(par_list->path, par_list->cmd_array, NULL);
		close(fd[1]);
		// exit(EXIT_SUCCESS);
	}
	else
	{
		wait(0);
		close(fd[1]);
		read(fd[0], buffer, 100);
		close(fd[0]);
		if(ft_strncmp(par_list->cmd_array[0], "cat", 3) == 0 && buffer != NULL)
			printf("Message from child: '%s'\n", buffer);
		// exit(EXIT_SUCCESS);
	}
}

// void set_signal_action(void)
// {
// 	struct sigaction	act;
// 	struct sigaction	act_signal;

// 	bzero(&act, sizeof(act));
// 	bzero(&act_signal, sizeof(act_signal));
// 	act.sa_handler = &sigint_handler;
// 	act_signal.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &act, NULL);
// 	sigaction(SIGQUIT, &act_signal, NULL);
// }