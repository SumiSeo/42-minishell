/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:11:59 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/19 16:37:48 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*casted_pointer;

	casted_pointer = (char *)s;
	i = 0;
	while (i < n)
	{
		*casted_pointer = '\0';
		i++;
		casted_pointer++;
	}
}

/*
int	main(void)
{
	char	str[] = "TESTis for Testing";
	char	str2[] = " I am testing this one";

	printf("original function -> %s <-\n", str);
	bzero(str, 1);
	printf("original function -> %s <-\n", str);
	printf("my function-> %s <-\n",str2);
	ft_bzero(str2, 1);
	printf("my function -> %s <-\n", str2);
}
*/
