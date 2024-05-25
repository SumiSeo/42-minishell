/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:51:50 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/20 14:12:38 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*allocate_empty_string(void)
{
	char	*casted_s;

	casted_s = (char *)malloc(1 * sizeof(char));
	if (!casted_s)
		return (NULL);
	casted_s[0] = '\0';
	return (casted_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*casted_s;
	size_t	i;
	size_t	total;
	size_t	input_length;

	input_length = ft_strlen(s);
	i = 0;
	total = len;
	if (!s)
		return (NULL);
	if (start >= input_length)
		return (allocate_empty_string());
	if (start + len > input_length)
		total = input_length - start;
	casted_s = (char *)malloc((total + 1) * sizeof(char));
	if (!casted_s)
		return (NULL);
	while (i < total)
	{
		casted_s[i] = s[start + i];
		i++;
	}
	casted_s[i] = '\0';
	return (casted_s);
}
/*
int	main(void)
{
	char			*nouvelle;
	unsigned int	index;
	size_t			length;

	nouvelle = "tripouille";
	index = 0;
	length = 42000;
	printf("my function test -> %s\n", ft_substr(nouvelle, index, length));
	printf("my function test ->%p\n", ft_substr(nouvelle, index, length));
}
*/
