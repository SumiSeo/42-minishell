/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:47:11 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/10 09:45:01 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (8);
	else
		return (0);
}

/*
int	main(void)
{
	char	test;

	test = '0';
	printf("original function -> %d\n",isalnum(test));
	printf("my function -> %d\n",ft_isalnum(test));
}
*/