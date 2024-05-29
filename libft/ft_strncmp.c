/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:10:49 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/19 20:30:31 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(s1 + i) == '\0' || *(unsigned char *)(s1
				+ i) != *(unsigned char *)(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char *s1 = "Tripouille";
	char *s2 = "tripouille";
	size_t n = 7;

	printf("What is the answer -> %d\n", strncmp(s1, s2, n));
	printf("What is the answer -> %d\n", ft_strncmp(s1, s2, n));

}*/
