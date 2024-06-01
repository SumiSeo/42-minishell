/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:02 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/31 19:20:24 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_env(t_envp *begin)
{
	while (begin)
	{
		printf("%s\n", begin->str);
		begin = begin->next;
	}
}

void	push_env(t_envp **p, const char *str, int len)
{
	t_envp	*element;
	t_envp	*last;

	last = *p;
	element = malloc(sizeof(t_envp));
	element->str = malloc(len + 1);
	ft_strlcpy(element->str, str, len + 1);
	element->next = NULL;
	if (*p == NULL)
	{
		*p = element;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

void	store_env(char **envp, t_envp **env)
{
	int i;
	int len;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		push_env(env, envp[i], len);
		i++;
	}
}