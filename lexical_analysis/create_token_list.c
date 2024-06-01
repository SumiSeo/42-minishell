/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 15:49:19 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	push_token_list(t_token **tok_list, const char *str, int len)
{
	t_token	*element;
	t_token	*last;

	last = *tok_list;
	element = malloc(sizeof(t_token));
	element->str = malloc(len + 1);
	ft_strlcpy(element->str, str, len + 1);
	element->next = NULL;
	if (*tok_list == NULL)
	{
		*tok_list = element;
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

void	create_token_list(char const *str, t_token **tok_list)
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
		push_token_list(tok_list, str + i, len);
		i = i + len;
	}
}

void	display_token_list(t_token *tok_list)
{
	while (tok_list)
	{
		printf("[%s]\n", tok_list->str);
		tok_list = tok_list->next;
	}
}