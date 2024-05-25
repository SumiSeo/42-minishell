/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/25 13:10:10 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_input(char const *str)
{
	int	i;
	int	double_quotes;
	int	single_quotes;

	double_quotes = 0;
	single_quotes = 0;
	i = 0;
	if ((str[i] < 97 || str[i] > 122))
	{
		printf("Error : Not lowercase character\n");
		return (1);
	}
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			double_quotes++;
		else if (str[i] == 39)
			single_quotes++;
		i++;
	}
	if (double_quotes > 0 && double_quotes % 2 != 0)
	{
		printf("Error : Quotes\n");
		return (1);
	}
	else if (single_quotes > 0 && single_quotes % 2 != 0)
	{
		printf("Error : Quotes\n");
		return (1);
	}
	return (0);
}

void	push(t_list **p, const char *str, int len)
{
	t_list	*element;
	t_list	*last;

	last = *p;
	element = malloc(sizeof(t_list));
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

int	get_len(char const *str, char c)
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
		while (str[len] != c && str[len] != '\0' && str[len] != '"' && str[len] != 39 && str[len] != '|' && str[len] != '>')
			len++;
	}
	// printf("len: %d\n", len);
	return (len);
}

void	create_list(char const *str, char c, t_list **lexer)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] != '\0')
	{
		len = 0;
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		len = get_len(str + i, c);
		push(lexer, str + i, len);
		i = i + len;
	}
}

// static char	*stringdup(char const *src, char c)
// {
// 	char	*dest;
// 	int		len;
// 	int		i;

// 	len = 0;
// 	i = 0;
// 	while (src[len] != c && src[len] != '\0')
// 		len++;
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	if (dest == NULL)
// 		return (NULL);
// 	while (src[i] != '\0' && i < len)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// static char	*findstring(char const *s, int *ptr_i_string, char c)
// {
// 	int		i;
// 	char	*dest;

// 	i = *ptr_i_string;
// 	while (s[i] != '\0' && s[i] == c)
// 		i++;
// 	if (s[i] != '\0')
// 		dest = stringdup(s + i, c);
// 	while (s[i] != c && s[i] != '\0')
// 		i++;
// 	*ptr_i_string = i;
// 	return (dest);
// }

// int	freearray(char **array, int wordnbr)
// {
// 	int	i;

// 	i = 0;
// 	while (i < wordnbr)
// 	{
// 		free(array[i]);
// 		i++;
// 	}
// 	free(array);
// 	return (0);
// }

// static int	countwords(char const *str, char c)
// {
// 	int	i;
// 	int	n;

// 	i = 0;
// 	n = 0;
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] == c && str[i] != '\0')
// 			i++;
// 		if (str[i] != '\0')
// 			n++;
// 		while (str[i] != c && str[i] != '\0')
// 			i++;
// 	}
// 	return (n);
// }

// static char	*stringdup(char const *src, char c)
// {
// 	char	*dest;
// 	int		len;
// 	int		i;

// 	len = 0;
// 	i = 0;
// 	while (src[len] != c && src[len] != '\0')
// 		len++;
// 	dest = (char *)malloc(sizeof(char) * (len + 1));
// 	if (dest == NULL)
// 		return (NULL);
// 	while (src[i] != '\0' && i < len)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// static char	*findstring(char const *s, int *ptr_i_string, char c)
// {
// 	int		i;
// 	char	*dest;

// 	i = *ptr_i_string;
// 	while (s[i] != '\0' && s[i] == c)
// 		i++;
// 	if (s[i] != '\0')
// 		dest = stringdup(s + i, c);
// 	while (s[i] != c && s[i] != '\0')
// 		i++;
// 	*ptr_i_string = i;
// 	return (dest);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**array;
// 	int		wordsnbr;
// 	int		i_string;
// 	int		i_array;
// 	int		*ptr_i_string;

// 	if (s == 0)
// 		return (0);
// 	i_array = 0;
// 	i_string = 0;
// 	ptr_i_string = &i_string;
// 	wordsnbr = countwords(s, c);
// 	array = (char **)malloc(sizeof(char *) * (wordsnbr + 1));
// 	if (array == NULL)
// 		return (NULL);
// 	while (i_array < wordsnbr)
// 	{
// 		array[i_array] = findstring(s, ptr_i_string, c);
// 		if (array[i_array] == NULL)
// 			freearray(array, wordsnbr);
// 		i_array++;
// 	}
// 	array[i_array] = NULL;
// 	return (array);
// }

/////////////////////////////////////////////////////////////////////

// // function for finding pipe 
// int	parse_pipe(char	*input_string, char	**strpiped)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 2)
// 	{
// 		strpiped[i] = strsep(&input_string, "|");
// 		if (strpiped[i] == NULL)
// 			break ;
// 		i++;
// 	}
// 	if (strpiped[1] == NULL)
// 		return (0);
// 	else
// 		return (1);
// }

// // function for parsing command words 
// void	parse_space(char *str, char **parsed_args)
// {
// 	int	i;

// 	i = 0;
// 	while (i < MAXLIST)
// 	{
// 		parsed_args[i] = strsep(&str, " ");
// 		// printf("%s\n", parsed_args[i]);
// 		if (parsed_args[i] == NULL)
// 			break ;
// 		if (strlen(parsed_args[i]) == 0)
// 			i--;
// 		i++;
// 	}
// }

// int	process_string(char	*input_string, char	**parsed_args, char	**parsed_args_piped)
// {
// 	char	*strpiped[2];
// 	int		piped;

// 	piped = 0;
// 	piped = parse_pipe(input_string, strpiped);
// 	if (piped)
// 	{
// 		parse_space(strpiped[0], parsed_args);
// 		parse_space(strpiped[1], parsed_args_piped);
// 	}
// 	else
// 	{
// 		parse_space(input_string, parsed_args);
// 	}
// 	return (piped);
// }
