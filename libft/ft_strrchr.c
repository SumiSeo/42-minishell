/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:50:31 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/20 11:41:47 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (c == 0)
		return ((char *)(s + length));
	while (length > 0)
	{
		if (s[length - 1] == (char)c)
			return ((char *)(s + length - 1));
		length--;
	}
	return (NULL);
}

/*
int	main(void)
{
	char str[] = "sumi seo";
	char c = 0;

	printf("Returned value -> %s\n", strrchr(str,c));
	printf("my Returned value -> %s\n", ft_strrchr(str,c));
}*/
