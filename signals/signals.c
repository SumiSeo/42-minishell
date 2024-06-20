/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:19:25 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/20 18:26:18 by ftanon           ###   ########.fr       */
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
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
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