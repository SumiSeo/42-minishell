/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:07:50 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/24 15:23:24 by ftanon           ###   ########.fr       */
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

static int	countwords(char const *str, char c)
{
	int	i;
	int	n;
	int	quoted;

	quoted = 0;
	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '"' || str[i] == 39)
		{
			printf("[%d]", n);
			printf("[");
			printf("%c", str[i]);
			i++;
			while (str[i] != '\0' && str[i] != '"' && str[i] != 39)
			{
				printf("%c", str[i]);
				i++;
			}
			printf("%c", str[i]);
			printf("]");
			n++;
		}
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			printf("[%d]", n);
			printf("[");
			printf("%c", str[i]);
			printf("%c", str[i + 1]);
			printf("]");
			i++;
			n++;
		}
		else if (str[i] == '<' && str[i + 1] == '<')
		{
			printf("[%d]", n);
			printf("[");
			printf("%c", str[i]);
			printf("%c", str[i + 1]);
			printf("]");
			i++;
			n++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			printf("[%d]", n);
			printf("[");
			printf("%c", str[i]);
			printf("]");
			n++;
		}
		else
		{
			printf("[%d]", n);
			printf("[");
			while (str[i] != c && str[i] != '\0' && str[i] != '"' && str[i] != 39 && str[i] != '|' && str[i] != '>')
			{
				printf("%c", str[i]);
				i++;
			}
			printf("]");
			n++;
			if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			{
				printf("\n");
				printf("[%d]", n);
				printf("[");
				printf("%c", str[i]);
				printf("]");
				n++;
			}
		}
		if (str[i] != '\0')
			i++;
		printf("\n");
	}
	printf("words : %d\n", n);
	return (n);
}

static char	*stringdup(char const *str, char c)
{
	char	*dest;
	int		len;
	int		i;

	dest = NULL;
	len = 0;
	i = 0;
	if (str[len] == '"' || str[len] == 39)
	{
		len++;
		while (str[len] != '\0' && str[len] != '"' && str[len] != 39)
			len++;
		len++;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		len = 2;
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		len = 2;
	}
	else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		len = 1;
	}
	else
	{
		while (str[len] != c && str[len] != '\0' && str[len] != '"' && str[len] != 39 && str[len] != '|' && str[len] != '>')
		{
			len++;
		}
	}
	// printf("len: %d\n", len);
	// while (src[len] != c && src[len] != '\0')
	// 	len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (str[i] != '\0' && i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*findstring(char const *str, int *ptr_i_string, char c)
{
	int		i;
	char	*dest;

	// dest = NULL;
	i = *ptr_i_string;
	while (str[i] != '\0' && str[i] == c)
		i++;
	// printf("pos: %c %d ", str[i], i);
	if (str[i] != '\0')
		dest = stringdup(str + i, c);
	if (str[i] == '"' || str[i] == 39)
	{
		i++;
		while (str[i] != '\0' && str[i] != '"' && str[i] != 39)
			i++;
		i++;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		i = i + 2;
	}
	else if (str[i] == '<' && str[i + 1] == '<')
	{
		i = i + 2;
	}
	else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		i = i + 1;
	}
	else
	{
		while (str[i] != c && str[i] != '\0' && str[i] != '"' && str[i] != 39 && str[i] != '|' && str[i] != '>')
		{
			i++;
		}
	}
	*ptr_i_string = i;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	// printf("%s\n", s);
	// printf("%c\n", c);
	char	**array;
	// array = NULL;
	int		wordsnbr;
	int		i_string;
	int		i_array;
	int		*ptr_i_string;

	// if (s == 0)
		// return (0);
	i_array = 0;
	i_string = 0;
	ptr_i_string = &i_string;
	wordsnbr = countwords(s, c);
	array = (char **)malloc(sizeof(char *) * (wordsnbr + 1));
	if (array == NULL)
		return (NULL);
	// array[i_array] = findstring(s, ptr_i_string, c);
	while (i_array < wordsnbr)
	{
		// printf("%d\n", *ptr_i_string);
		array[i_array] = findstring(s, ptr_i_string, c);
		printf("[%d]", i_array);
		printf("[%s]\n", array[i_array]);
		// if (array[i_array] == NULL)
		// 	freearray(array, wordsnbr);
		i_array++;
	}
	// array[i_array] = NULL;
	return (array);
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
