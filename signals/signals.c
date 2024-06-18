/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:19:25 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/18 19:19:28 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		print_dir();
	}
}

void set_signal_action(void)
{
	struct sigaction	act;
	struct sigaction	act_signal;

	bzero(&act, sizeof(act));
	bzero(&act_signal, sizeof(act_signal));
	act.sa_handler = &sigint_handler;
	act_signal.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act_signal, NULL);
}