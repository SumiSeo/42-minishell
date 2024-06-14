/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/14 13:38:36 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

int	is_double_bracket(char c, char d)
{
	if (c == '>' && d == '>')
		return (1);
	else if (c == '<' && d == '<')
		return (1);
	else
		return (0);
}

int	is_bracket_pipe(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	not_operator_dollar(char c)
{
	if (c != ' ' && c != '\0' && c != '"'
		&& c != 39 && c != '|' && c != '>' && c != '$')
		return (1);
	else
		return (0);
}

int	not_operator(char c)
{
	if (c != ' ' && c != '\0' && c != '"'
		&& c != 39 && c != '|' && c != '>')
		return (1);
	else
		return (0);
}

int	not_space_pipe(char c)
{
	if (c != ' ' && c != '\0' && c != '|')
		return (1);
	else
		return (0);
}

int	not_double_quote(char c)
{
	if (c != '"' && c != '\0')
		return (1);
	else
		return (0);
}

int	not_single_quote(char c)
{
	if (c != 39 && c != '\0')
		return (1);
	else
		return (0);
}

int	is_space(char c)
{
	if (c == ' ' && c != '\0')
		return (1);
	else
		return (0);
}

char	*env_path(t_env *env_list, int len, char *string)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->env_var, string, len) == 0)
			return (env_list->env_var + len + 1);
		env_list = env_list->next;
	}
	return (NULL);
}

void	expand_len_pos(t_data *data, t_env *env_list, t_token *element)
{
	int		i;
	int		len;
	char	*string;
	char	*result;

	data->pos++;
	i = data->pos;
	len = 0;
	while (not_operator_dollar(data->input[i]))
	{
		i++;
		len++;
	}
	string = malloc (sizeof(char) * (len +1));
	ft_strlcpy(string, data->input + data->pos, len + 1);
	result = env_path(env_list, len, string);
	data->pos = data->pos + i;
	if (result == NULL)
		element->len = 0;
	else
		element->len = element->len + ft_strlen(result);
}

void	double_quote_len(t_data *data, t_env *env_list, t_token	*element)
{
	data->pos++;
	while (not_double_quote(data->input[data->pos]))
	{
		if (data->input[data->pos] == '$')
		{
			expand_len_pos(data, env_list, element);
		}
		else
		{
			element->len++;
			data->pos++;
		}
	}
	if (data->input[data->pos] != '\0')
		data->pos++;
}

void	no_quote_len(t_data *data, t_env *env_list, t_token	*element)
{
	while (not_operator(data->input[data->pos]))
	{
		if (data->input[data->pos] == '$')
		{
			expand_len_pos(data, env_list, element);
		}
		else
		{
			element->len++;
			data->pos++;
		}
	}
}

void	single_quote_len(t_data *data, t_token	*element)
{
	data->pos++;
	while (not_single_quote(data->input[data->pos]))
	{
		element->len++;
		data->pos++;
	}
	if (data->input[data->pos] != '\0')
		data->pos++;
}

void	get_len_pos(t_data *data, t_env *env_list, t_token	*element)
{
	if (is_double_bracket(data->input[data->pos], data->input[data->pos + 1]))
	{
		element->len = 2;
		data->pos = data->pos + 2;
	}	
	else if (is_bracket_pipe(data->input[data->pos]))
	{
		element->len = 1;
		data->pos = data->pos + 1;
	}
	else
	{
		while (not_space_pipe(data->input[data->pos]))
		{
			if (data->input[data->pos] == '"')
				double_quote_len(data, env_list, element);
			else if (data->input[data->pos] == 39)
				single_quote_len(data, element);
			else
				no_quote_len(data, env_list, element);
		}
	}
}

int	get_the_length(char *str)
{
	int	i;

	i = 0;
	while (not_operator_dollar(str[i]))
	{
		i++;
	}
	return (i);
}

void	copy_word(t_token *element, char *str)
{
	element->word[element->j] = str[element->i];
	element->i++;
	element->j++;
}

void	expand_word(t_token *element, char *str, t_env *env_list)
{
	int		src_len;
	int		k;
	char	*src;
	char	*dst;

	element->i++;
	src_len = get_the_length(str + element->i);
	src = malloc (sizeof(char) * (src_len +1));
	ft_strlcpy(src, str + element->i, src_len + 1);
	dst = env_path(env_list, src_len, str + element->i);
	if (dst == NULL)
		element->word[element->j] = '\0';
	else
	{
		k = 0;
		while (dst[k])
		{
			element->word[element->j] = dst[k];
			k++;
			element->j++;
		}
	}
	element->i = element->i + src_len;
}

void	operator(t_token *element, char *str)
{
	element->operator = malloc(element->len + 1);
	element->word = NULL;
	ft_strlcpy(element->operator, str, element->len + 1);
}

void	double_quote(t_token *element, char *str, t_env *env_list)
{
	element->i++;
	while (str[element->i] != '\0' && str[element->i] != '"')
	{
		if (str[element->i] == '$')
			expand_word(element, str, env_list);
		else
			copy_word(element, str);
	}
	if (str[element->i] != '\0')
		element->i++;
}

void	single_quote(t_token *element, char *str)
{
	element->i++;
	while (str[element->i] != '\0' && str[element->i] != 39)
		copy_word(element, str);
	if (str[element->i] != '\0')
		element->i++;
}

void	no_quote(t_token *element, char *str, t_env *env_list)
{
	while (not_operator(str[element->i]))
	{
		if (str[element->i] == '$')
			expand_word(element, str, env_list);
		else
			copy_word(element, str);
	}
}

void	add_string(t_token *element, char *str, t_env *env_list)
{
	if (is_operator(str[0]))
		operator(element, str);
	else
	{
		element->word = malloc(element->len + 1);
		element->operator = NULL;
		while (not_space_pipe(str[element->i]))
		{
			if (str[element->i] == '"')
				double_quote(element, str, env_list);
			else if (str[element->i] == 39)
				single_quote(element, str);
			else
				no_quote(element, str, env_list);
		}
		element->word[element->j] = '\0';
	}
}

void	push_token_list(t_token **tok_list, char *str, t_env *env, t_data *data)
{
	t_token	*element;
	t_token	*last;

	last = *tok_list;
	element = malloc(sizeof(t_token));
	element->j = 0;
	element->i = 0;
	element->len = 0;
	get_len_pos(data, env, element);
	add_string(element, str, env);
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

// **** attention segfault
// tok_list = NULL;
void	create_token_list(t_data *data, t_token **tok_list, t_env *env_list)
{
	data->pos = 0;
	while (data->input[data->pos] != '\0')
	{
		while (is_space(data->input[data->pos]))
			data->pos++;
		if (data->input[data->pos] == '\0')
			break ;
		push_token_list(tok_list, data->input + data->pos, env_list, data);
	}
}

void	display_token_list(t_token *tok_list)
{
	tok_list->num = 0;
	while (tok_list)
	{
		if (tok_list->word)
			printf("[%s]\n", tok_list->word);
		if (tok_list->operator)
			printf("%s\n", tok_list->operator);
		tok_list = tok_list->next;
	}
}

//---------------------------------------------------------------- V6

// int	expand_pos(t_data *data)
// {
// 	int		i;
// 	int		pos;

// 	i = data->pos;
// 	pos = 0;
// 	i++;
// 	while (not_operator_dollar(data->input[i]))
// 	{
// 		i++;
// 		pos++;
// 	}
// 	return (pos);
// }

// int	expand_len(t_data *data, t_env *env_list)
// {
// 	int		i;
// 	int		len;
// 	char	*string;
// 	char	*result;

// 	string = NULL;
// 	i = data->pos;
// 	len = 0;
// 	i++;
// 	while (not_operator_dollar(data->input[i]))
// 	{
// 		i++;
// 		len++;
// 	}
// 	string = malloc (sizeof(char) * (len +1));
// 	ft_strlcpy(string, data->input + data->pos + 1, len + 1);
// 	result = env_path(env_list, len, string);
// 	if (result == NULL)
// 		return (0);
// 	return (ft_strlen(result));
// }

//---------------------------------------------------------------- V5

// int	get_len(t_data *data, t_env *env_list)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	if (is_double_bracket(data))
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}	
// 	else if (is_double_bracket(data))
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}
// 	else if (is_bracket_pipe(data))
// 	{
// 		len = 1;
// 		data->position = data->position + 1;
// 	}
// 	else
// 	{
// 		while (not_operator_3(data->input_string[data->position]))
// 		{
// 			if (data->input_string[data->position] == '"')
// 			{
// 				data->position++;
// 				while (not_double_quote(data->input_string[data->position]))
// 				{
// 					if (data->input_string[data->position] == '$')
// 					{
// 						len = len + expansion_len(data, env_list);
// 						data->position = data->position + expansion_pos(data) + 1;
// 					}
// 					else
// 					{
// 						len++;
// 						data->position++;
// 					}
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else if (data->input_string[data->position] == 39)
// 			{
// 				data->position++;
// 				while (not_single_quote(data->input_string[data->position]))
// 				{
// 					len++;
// 					data->position++;
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else
// 			{
// 				while (not_operator_6(data->input_string[data->position]))
// 				{
// 					if (data->input_string[data->position] == '$')
// 					{
// 						len = len + expansion_len(data, env_list);
// 						data->position = data->position + expansion_pos(data) + 1;
// 					}
// 					else
// 					{
// 						len++;
// 						data->position++;
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return (len);
// }

//---------------------------------------------------------------- OLD $

					// if (str[element->i] == '$')
					// {
					// 	element->i++;
					// 	src_len = get_the_length(str + element->i);
					// 	// while (str[element->i] != ' ' && str[element->i] != '\0' && str[element->i] != '"' && str[element->i] != 39 && str[element->i] != '|' && str[element->i] != '>' && str[element->i] != '$')
					// 	// {
					// 		// element->i++;
					// 		// src_len++;
					// 	// }
					// 	// printf("%d\n", src_len);
					// 	// printf("%d\n", i);
					// 	// printf("%c\n", str[element->i]);
					// 	// printf("%s\n", element->word);
					// 	printf("-----\n");
					// 	printf("%s\n", element->word);
					// 	printf("%d\n", src_len);
					// 	printf("-----\n");
					// 	// printf("%d\n", src_len);
					// 	// printf("%d\n", dst_len);
					// 	// element->word = malloc(dst_len + 1);
					// 	// element->operator = NULL;
					// 	src = malloc (sizeof(char) * (src_len +1));
					// 	ft_strlcpy(src, str + element->i, src_len + 1);
					// 	dst = env_path(env_list, src_len, str + element->i);
					// 	printf("%s\n", dst);
					// 	if (dst == NULL)
					// 	{
					// 		printf("env not found\n");
					// 		element->word[element->j] = '\0';
					// 	}
					// 	else
					// 	{
					// 		k = 0;
					// 		printf("-----\n");
					// 		printf("env found\n");
					// 		printf("%d\n", dst_len);
					// 		printf("%s\n", dst);
					// 		// printf("%d\n", j);
					// 		printf("%s\n", element->word);
					// 		printf("-----\n");
					// 		// ft_strlcpy(element->word + j, dst, dst_len + 1);
					// 		while (dst[k])
					// 		{
					// 			// printf("%c",dst[k]);
					// 			element->word[element->j] = dst[k];
					// 			k++;
					// 			element->j++;
					// 		}
					// 		// j = j + dst_len;
					// 		printf("%s\n", element->word);
					// 	}
					// 	element->i = element->i + src_len;
					// 	// printf("%d\n", dst_len);
					// }

//---------------------------------------------------------------- V3

// int	get_len(t_data *data, t_env *env_list)
// {
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = 0;
// 	if (data->input_string[data->position] == '$')
// 	{
// 		len = expansion_len(data, env_list);
// 		data->position = data->position + expansion_pos(data) + 1;
// 	}
// 	else if (data->input_string[data->position] == '>' && data->input_string[data->position + 1] == '>')
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}	
// 	else if (data->input_string[data->position] == '<' && data->input_string[data->position + 1] == '<')
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}
// 	else if (data->input_string[data->position] == '|' || data->input_string[data->position] == '>' || data->input_string[data->position] == '<')
// 	{
// 		len = 1;
// 		data->position = data->position + 1;
// 	}
// 	else
// 	{
// 		while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '|')
// 		{
// 			if (data->input_string[data->position] == '"')
// 			{
// 				data->position++;
// 				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != '"')
// 				{
// 					len++;
// 					data->position++;
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else if (data->input_string[data->position] == 39)
// 			{
// 				data->position++;
// 				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != 39)
// 				{
// 					len++;
// 					data->position++;
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else
// 			{
// 				while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '"' && data->input_string[data->position] != 39 && data->input_string[data->position] != '|' && data->input_string[data->position] != '>')
// 				{
// 					data->position++;
// 					len++;
// 				}
// 			}
// 		}
// 	}
// 	return (len);
// }

//---------------------------------------------------------------- V2

// int	get_len(t_data *data, t_env *env_list)
// {
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = 0;
// 	if (data->input_string[data->position] == '$')
// 	{
// 		len = expansion_len(data, env_list);
// 		data->position = data->position + expansion_pos(data) + 1;
// 	}
// 	else if (data->input_string[data->position] == '>' && data->input_string[data->position + 1] == '>')
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}	
// 	else if (data->input_string[data->position] == '<' && data->input_string[data->position + 1] == '<')
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}
// 	else if (data->input_string[data->position] == '|' || data->input_string[data->position] == '>' || data->input_string[data->position] == '<')
// 	{
// 		len = 1;
// 		data->position = data->position + 1;
// 	}
// 	else
// 	{
// 		while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '|')
// 		{
// 			if (data->input_string[data->position] == '"')
// 			{
// 				data->position++;
// 				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != '"')
// 				{
// 					len++;
// 					data->position++;
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else if (data->input_string[data->position] == 39)
// 			{
// 				data->position++;
// 				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != 39)
// 				{
// 					len++;
// 					data->position++;
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else
// 			{
// 				while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '"' && data->input_string[data->position] != 39 && data->input_string[data->position] != '|' && data->input_string[data->position] != '>')
// 				{
// 					data->position++;
// 					len++;
// 				}
// 			}
// 		}
// 	}
// 	return (len);
// }


//---------------------------------------------------------------- V1

// int	get_len(t_data *data)
// {
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = 0;
// 	if (data->input_string[data->position] == '>' && data->input_string[data->position + 1] == '>')
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}	
// 	else if (data->input_string[data->position] == '<' && data->input_string[data->position + 1] == '<')
// 	{
// 		len = 2;
// 		data->position = data->position + 2;
// 	}
// 	else if (data->input_string[data->position] == '|' || data->input_string[data->position] == '>' || data->input_string[data->position] == '<')
// 	{
// 		len = 1;
// 		data->position = data->position + 1;
// 	}
// 	else
// 	{
// 		while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '|')
// 		{
// 			if (data->input_string[data->position] == '"')
// 			{
// 				data->position++;
// 				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != '"')
// 				{
// 					len++;
// 					data->position++;
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else if (data->input_string[data->position] == 39)
// 			{
// 				data->position++;
// 				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != 39)
// 				{
// 					len++;
// 					data->position++;
// 				}
// 				if (data->input_string[data->position] != '\0')
// 					data->position++;
// 			}
// 			else
// 			{
// 				while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '"' && data->input_string[data->position] != 39 && data->input_string[data->position] != '|' && data->input_string[data->position] != '>')
// 				{
// 					data->position++;
// 					len++;
// 				}
// 			}
// 		}
// 	}
// 	return (len);
// }

// void	push_token_list(t_token **tok_list, const char *str, int len)
// {
// 	t_token	*element;
// 	t_token	*last;

// 	last = *tok_list;
// 	element = malloc(sizeof(t_token));
// 	if (str[0] == '"' || str[0] == 39)
// 	{
// 		len = len -2;
// 		element->word = malloc(len + 1);
// 		element->operator = NULL;
// 		str++;
// 		ft_strlcpy(element->word, str, len + 1);
// 	}
// 	else if (str[0] == '>' || str[1] == '>' || str[0] == '|' || str[0] == '>'
// || str[0] == '<')
// 	{
// 		element->operator = malloc(len + 1);
// 		element->word = NULL;
// 		ft_strlcpy(element->operator, str, len + 1);
// 	}
// 	else
// 	{
// 		element->word = malloc(len + 1);
// 		element->operator = NULL;
// 		ft_strlcpy(element->word, str, len + 1);
// 	}
// 	element->next = NULL;
// 	if (*tok_list == NULL)
// 	{
// 		*tok_list = element;
// 		return ;
// 	}
// 	while (last->next != NULL)
// 		last = last->next;
// 	last->next = element;
// 	element->prev = last;
// }

// int	get_len(char const *str)
// {
// 	int		len;

// 	len = 0;
// 	if (str[0] == '"')
// 	{
// 		len++;
// 		while (str[len] != '\0' && str[len] != '"')
// 			len++;
// 		len++;
// 	}
// 	else if (str[0] == 39)
// 	{
// 		len++;
// 		while (str[len] != '\0' && str[len] != 39)
// 			len++;
// 		len++;
// 	}
// 	else if (str[0] == '>' && str[1] == '>')
// 		len = 2;
// 	else if (str[0] == '<' && str[1] == '<')
// 		len = 2;
// 	else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
// 		len = 1;
// 	else
// 	{
// 		while (str[len] != ' ' && str[len] != '\0' && str[len] != '"'
// && str[len] != 39 && str[len] != '|' && str[len] != '>')
// 			len++;
// 	}
// 	// printf("len: %d\n", len);
// 	return (len);
// }