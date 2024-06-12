/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/12 13:26:02 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	push_token_list(t_token **tok_list, char *str, int dst_len, t_env *env_list)
{
	t_token	*element;
	t_token	*last;
	int	i;
	int	j;
	char	*src;
	int		src_len;
	char 	*dst;

	i = 0;
	j = 0;
	src_len = 0;
	last = *tok_list;
	src = NULL;
	dst = NULL;
	element = malloc(sizeof(t_token));
	// printf("here %s\n", str);
	if (str[0] == '$')
	{
		while (str[i] != ' ' && str[i] != '\0' && str[i] != '"' && str[i] != 39 && str[i] != '|' && str[i] != '>')
		{
			i++;
			src_len++;
		}
		src_len--;
		element->word = malloc(dst_len + 1);
		element->operator = NULL;
		src = malloc (sizeof(char) * (src_len +1));
		ft_strlcpy(src, str + 1, src_len + 1);
		dst = env_path(env_list, src_len, str + 1);
		if (dst == NULL)
			element->word[0] = '\0';
		else
			ft_strlcpy(element->word, dst, dst_len + 1);
		printf("%s\n", str);
		printf("%s\n", dst);
		printf("%s\n", element->word);
	}
	else if (str[0] == '>' || str[0] == '>' || str[0] == '|' || str[0] == '>' || str[0] == '<')
	{
		element->operator = malloc(dst_len + 1);
		element->word = NULL;
		ft_strlcpy(element->operator, str, dst_len + 1);
	}
	else
	{
		element->word = malloc(dst_len + 1);
		element->operator = NULL;
		while (str[i] != ' ' && str[i] != '\0' && str[i] != '|')
		{
			if (str[i] == '"')
			{
				i++;
				while (str[i] != '\0' && str[i] != '"')
				{
					if (str[i] == '$')
					{
						while (str[i] != ' ' && str[i] != '\0' && str[i] != '"' && str[i] != 39 && str[i] != '|' && str[i] != '>')
						{
							i++;
							src_len++;
						}
						printf("%d\n", src_len);
						printf("%d\n", i);
						printf("%c\n", str[i]);
						src_len--;
						printf("%d\n", src_len);
						printf("%d\n", dst_len);
						element->word = malloc(dst_len + 1);
						element->operator = NULL;
						src = malloc (sizeof(char) * (src_len +1));
						ft_strlcpy(src, str + 2, src_len + 1);
						dst = env_path(env_list, src_len, str + 2);
						
						if (dst == NULL)
						{
							printf("la\n");
							element->word[0] = '\0';
						}
						else
						{
							printf("ici\n");
							ft_strlcpy(element->word, dst, dst_len + 1);
							j = j + dst_len;
							// printf("%s\n", element->word);
						}
						// printf("%d\n", dst_len);
					}
					else
					{
						element->word[j] = str[i];
						i++;
						j++;
					}
				}
				if (str[i] != '\0')
					i++;
				printf("%s\n", element->word);
			}
			else if (str[i] == 39)
			{
				i++;
				while (str[i] != '\0' && str[i] != 39)
				{
					element->word[j] = str[i];
					i++;
					j++;
				}
				if (str[i] != '\0')
					i++;
			}
			else
			{
				while (str[i] != ' ' && str[i] != '\0' && str[i] != '"' && str[i] != 39 && str[i] != '|' && str[i] != '>')
				{
					element->word[j] = str[i];
					i++;
					j++;
				}
			}
		}
		element->word[j] = '\0';
	}

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

int expansion_pos(t_data *data)
{
	int		i;
	int		pos;

	i = data->position;
	pos = 0;
	while (data->input_string[i] != ' ' && data->input_string[i] != '\0' && data->input_string[i] != '"' && data->input_string[i] != 39 && data->input_string[i] != '|' && data->input_string[i] != '>')
	{
		i++;
		pos++;
	}
	pos--;
	return (pos);
}

int expansion_len(t_data *data, t_env *env_list)
{
	int		i;
	int		len;
	char	*string;
	char	*result;

	string = NULL;
	i = data->position;
	len = 0;
	while (data->input_string[i] != ' ' && data->input_string[i] != '\0' && data->input_string[i] != '"' && data->input_string[i] != 39 && data->input_string[i] != '|' && data->input_string[i] != '>')
	{
		i++;
		len++;
	}
	len--;
	string = malloc (sizeof(char) * (len +1));
	ft_strlcpy(string, data->input_string + data->position + 1, len + 1);
	result = env_path(env_list, len, string);
	if (result == NULL)
		return (0);
	// printf("%s\n", string);
	// printf("%s\n", result);
	// printf("%zu\n", ft_strlen(result));
	return (ft_strlen(result));
}

int	get_len(t_data *data, t_env *env_list)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (data->input_string[data->position] == '$')
	{
		len = expansion_len(data, env_list);
		data->position = data->position + expansion_pos(data) + 1;
	}
	else if (data->input_string[data->position] == '>' && data->input_string[data->position + 1] == '>')
	{
		len = 2;
		data->position = data->position + 2;
	}	
	else if (data->input_string[data->position] == '<' && data->input_string[data->position + 1] == '<')
	{
		len = 2;
		data->position = data->position + 2;
	}
	else if (data->input_string[data->position] == '|' || data->input_string[data->position] == '>' || data->input_string[data->position] == '<')
	{
		len = 1;
		data->position = data->position + 1;
	}
	else
	{
		while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '|')
		{
			if (data->input_string[data->position] == '"')
			{
				data->position++;
				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != '"')
				{
					if (data->input_string[data->position] == '$')
					{
						len = len + expansion_len(data, env_list);
						data->position = data->position + expansion_pos(data) + 1;
					}
					else
						len++;
					data->position++;
				}
				if (data->input_string[data->position] != '\0')
					data->position++;
			}
			else if (data->input_string[data->position] == 39)
			{
				data->position++;
				while (data->input_string[data->position] != '\0' && data->input_string[data->position] != 39)
				{
					len++;
					data->position++;
				}
				if (data->input_string[data->position] != '\0')
					data->position++;
			}
			else
			{
				while (data->input_string[data->position] != ' ' && data->input_string[data->position] != '\0' && data->input_string[data->position] != '"' && data->input_string[data->position] != 39 && data->input_string[data->position] != '|' && data->input_string[data->position] != '>')
				{
					data->position++;
					len++;
				}
			}
		}
	}
	return (len);
}


void	create_token_list(t_data *data, t_token **tok_list, t_env *env_list)
{
	int	len;
	int	i;
	// **** attention segfault
	// tok_list = NULL;
	data->position = 0;
	i = 0;
	while (data->input_string[data->position] != '\0')
	{
		len = 0;
		while (data->input_string[data->position] == ' ' && data->input_string[data->position] != '\0')
			data->position++;
		i = data->position;
		if (data->input_string[data->position] == '\0')
			break ;
		len = get_len(data, env_list);
		printf("a: %d\n", len);
		printf("b: %s\n", data->input_string + i);
		// printf("here %s\n", env_list->env_var);
		push_token_list(tok_list, data->input_string + i, len, env_list);
		i = data->position;
	}
}

void	display_token_list(t_token *tok_list)
{
	while (tok_list)
	{
		if (tok_list->word)
			printf("[%s]\n", tok_list->word);
		if (tok_list->operator)
			printf("%s\n", tok_list->operator);
		tok_list = tok_list->next;
	}
}

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
// 	else if (str[0] == '>' || str[1] == '>' || str[0] == '|' || str[0] == '>' || str[0] == '<')
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
// 		while (str[len] != ' ' && str[len] != '\0' && str[len] != '"' && str[len] != 39 && str[len] != '|' && str[len] != '>')
// 			len++;
// 	}
// 	// printf("len: %d\n", len);
// 	return (len);
// }