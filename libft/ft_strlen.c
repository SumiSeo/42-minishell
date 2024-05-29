/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:44:13 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/10 10:15:31 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s != 0)
	{
		s++;
		length++;
	}
	return (length);
}

/*int main()
{
	char str[] = "Sumi";
	printf("original fun => %ld\n",strlen(str));
	printf("my func => %ld\n", ft_strlen(str));

}*/
