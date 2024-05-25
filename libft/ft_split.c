/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:46:13 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/20 16:45:07 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	**free_array(char **array, int count)
{
	while (count >= 0)
	{
		free(array[count]);
		count--;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	array = (char **)ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	j = 0;
	while (i < count_words(s, c))
	{
		while (s[k] == c)
			k++;
		j = k;
		while (s[k] && s[k] != c)
			k++;
		array[i] = (char *)ft_calloc((k - j + 1), sizeof(char));
		if (!array[i])
			return (free_array(array, i));
		ft_strlcpy(array[i++], &s[j], k - j + 1);
	}
	return (array);
}

/*
int	main(void)
{
	char *str= "----1--2-3-45--6-7-8";
	char c = '-';
	char **arr;
	arr = ft_split(str, c);
	printf("TEST VALUE : %c\n", arr[0][0]);
	printf("TEST VALUE : %c\n", arr[1][0]);
	printf("TEST VALUE : %c\n", arr[2][0]);
}*/
