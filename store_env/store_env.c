/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 18:10:02 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/31 18:10:41 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_env(t_envp *begin)
{
	while (begin)
	{
		printf("[%s]\n", begin->str);
		begin = begin->next;
	}
}

void	display_path(t_env *begin)
{
	display_array(begin->str);
	printf("nb pipes : %d\n", begin->has_pipe);
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
	int			i;
	int			len;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		push_env(env, envp[i], len);
		i++;
	}
}

void	store_path(t_envp *env, t_env *path)
{
	while (env)
	{
		if (ft_strncmp(env->str, "PATH", 4) == 0)
		{
			path->str = ft_split(env->str + 5, ':');
			break ;
		}
		env = env->next;
	}
}

void	count_nb_pipe(t_lexer *lexer, t_env *path)
{
	int		nb;

	path->has_pipe = 0;
	nb = 0;
	while (lexer)
	{
		if (lexer->str[0] == '|')
			nb++;
		lexer = lexer->next;
	}
	path->has_pipe = nb;
}