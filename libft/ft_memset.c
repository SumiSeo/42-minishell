/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:20:29 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/22 15:35:15 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(s + i) = c;
		i++;
	}
	return (s);
}

/*
int	main(void)
{
	char	str[] = "TEST is for Testing";
	char	str2[] = "TEST is for Testing";

	memset(str, '@', 5);
	ft_memset(str2, '@', 5);
	printf("original function -> %s\n", str);
	printf("original function returning ->%p\n", memset(str, '@', 5));
	printf("my function -> %s\n",str2);
	printf("myfunction returning ->%p\n", ft_memset(str2, '@', 5));
}

*/
