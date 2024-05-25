/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:40:24 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/19 18:03:05 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*casted_dest;
	char	*casted_src;

	casted_src = (char *)src;
	casted_dest = (char *)dest;
	if (dest > src)
	{
		while (n > 0)
		{
			casted_dest[n - 1] = casted_src[n - 1];
			n--;
		}
	}
	else if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			casted_dest[i] = casted_src[i];
			i++;
		}
	}
	return (casted_dest);
}

/*
int	main(void)
{

	char str[100] = "Learning is fun";
	char *first, *second;

	first =str;
	second = str;
	size_t size = 10;

	printf("original function %s",memmove(first, second, size));
	printf("my function %s\n", ft_memmove(first, second, size));
}*/
