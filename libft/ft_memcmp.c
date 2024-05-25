/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:33:04 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/19 19:51:30 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

/*
int	main(void)
{
	char	*s1;
	char	*s2;
	size_t	n;

	s1 = "Simi is programming";
	s2 = "Su is at 42";
	n = 2;
	printf("What is the answer -> %d\n", memcmp(s1, s2, n));
	printf("What is the answer -> %d\n", ft_memcmp(s1, s2, n));
}
*/
