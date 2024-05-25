/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:46:33 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/20 12:40:00 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;

	i = 0;
	total_size = count * size;
	if (count != 0 && total_size / count != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	while (i < total_size)
	{
		*((char *)ptr + i) = 0;
		i++;
	}
	return (ptr);
}
/*

int	main(void)
{
	size_t	num;
	size_t	byte;

	num = 4;
	byte = 0;
	printf("what is returned from original calloc %p\n", calloc(num,byte));
	printf("what is returned from my calloc %p\n", ft_calloc(num, byte));
}
*/
