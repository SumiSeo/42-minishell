/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:56:04 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/18 13:29:11 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		length;
	char	*new_s;
	int		i;

	i = 0;
	length = 0;
	while (s[length])
		length++;
	new_s = (char *)malloc(sizeof(char) * (length + 1));
	if (!s)
		return (NULL);
	if (!new_s)
		return (NULL);
	if (s && f)
	{
		while (s[i] != '\0')
		{
			new_s[i] = f(i, s[i]);
			i++;
		}
	}
	new_s[i] = '\0';
	return (new_s);
}

/*
static char	sumi(unsigned int i, char s)
{
	printf("int %d\n",i);
	printf("int %c\n",s);
	return (s);
}

int	main(void)
{
	char	*s;

	s = "Test string";
	printf("final result : %s\n", ft_strmapi(s,sumi));
}
*/