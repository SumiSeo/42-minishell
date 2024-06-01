/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:01:57 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 16:34:23 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_operator(t_token *tok_list)
{
	int		len;

	len = 0;
	while (tok_list && tok_list->str[0] != '|' && tok_list->str[0] != '>' && tok_list->str[0] != '<')
	{
		len++;
		tok_list = tok_list->next;
	}
	return (len);
}

int	count_words_pipe_search(t_token *tok_list)
{
	int		len;

	len = 0;
	while (tok_list && tok_list->str[0] != '|')
	{
		len++;
		tok_list = tok_list->next;
	}
	return (len);
}

void	split_command(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	k;
	int	j;
	int	len;

	len = 0;
	j = 0;
	while (tok_list && tok_list->str[0] != '|')
	{
		i = 0;
		k = 0;
		if (tok_list->str[0] == '>' || tok_list->str[0] == '<')
			i = 2;
		else
			i = count_words_operator(tok_list);
		if (tok_list->str[0] == '<')
		{
			len = ft_strlen(tok_list->str);
			par_list->infile_token = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(par_list->infile_token, tok_list->str, len + 1);
			tok_list = tok_list->next;
			len = ft_strlen(tok_list->str);
			par_list->infile_name = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(par_list->infile_name, tok_list->str, len + 1);
			tok_list = tok_list->next;
		}
		else if (tok_list->str[0] == '>')
		{
			len = ft_strlen(tok_list->str);
			par_list->outfile_token = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(par_list->outfile_token, tok_list->str, len + 1);
			tok_list = tok_list->next;
			len = ft_strlen(tok_list->str);
			par_list->outfile_name = (char *)malloc(sizeof(char) * (len + 1));
			ft_strlcpy(par_list->outfile_name, tok_list->str, len + 1);
			tok_list = tok_list->next;
		}
		else
		{
			par_list->cmd_array = (char **)malloc(sizeof(char *) * (i + 1));
			while (tok_list && tok_list->str[0] != '|' && tok_list->str[0] != '>' && tok_list->str[0] != '<')
			{
				len = ft_strlen(tok_list->str);
				par_list->cmd_array[j] = (char *)malloc(sizeof(char) * (len + 1));
				ft_strlcpy(par_list->cmd_array[j], tok_list->str, len + 1);
				j++;
				tok_list = tok_list->next;
			}
			par_list->cmd_array[j] = NULL;
		}
	}
}

void	store_command(t_token *tok_list, t_parse *par_list)
{
	int	i;
	int	k;

	while (par_list)
	{
		i = 0;
		k = 0;
		i = count_words_pipe_search(tok_list);
		split_command(tok_list, par_list);
		while (k < i)
		{
			tok_list = tok_list->next;
			k++;
		}
		if (tok_list && tok_list->str[0] == '|')
			tok_list = tok_list->next;
		par_list = par_list->next;
	}
}