/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:46:57 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/20 11:41:13 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little || little[0] == '\0')
		return ((char *)(big));
	if (!big)
		return ((char *)(big + i));
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] != '\0' && i + j < len)
		{
			if (little[j] != big[i + j])
				break ;
			j++;
		}
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	*largestring;
	char	*smallstring;
	size_t	size;

		largestring = "Hello world";
		smallstring = "lo";
		size = 10;
		printf("returned value -> %s\n", ft_strnstr(largestring, smallstring,
				size));
}
*/
