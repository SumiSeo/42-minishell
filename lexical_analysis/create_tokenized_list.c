/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokenized_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/30 18:08:01 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



void	push_lexer(t_lexer **p, const char *str, int len)
{
	t_lexer	*element;
	t_lexer	*last;

	last = *p;
	element = malloc(sizeof(t_lexer));
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

int	get_len(char const *str)
{
	int		len;

	len = 0;
	if (str[0] == '"' || str[0] == 39)
	{
		len++;
		while (str[len] != '\0' && str[len] != '"' && str[len] != 39)
			len++;
		len++;
	}
	else if (str[0] == '>' && str[1] == '>')
		len = 2;
	else if (str[0] == '<' && str[1] == '<')
		len = 2;
	else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		len = 1;
	else
	{
		while (str[len] != ' ' && str[len] != '\0' && str[len] != '"' && str[len] != 39 && str[len] != '|' && str[len] != '>')
			len++;
	}
	// printf("len: %d\n", len);
	return (len);
}

void	create_tokenized_list(char const *str, t_lexer **lexer)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] != '\0')
	{
		len = 0;
		while (str[i] == ' ' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		len = get_len(str + i);
		push_lexer(lexer, str + i, len);
		i = i + len;
	}
}

void	display_lexer(t_lexer *begin)
{
	while (begin)
	{
		printf("[%s]\n", begin->str);
		begin = begin->next;
	}
}