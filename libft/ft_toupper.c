/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:14:48 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/10 18:24:20 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	else
		return (c);
}

/*
int	main(void)
{
	char	alpha;

	alpha = 'b';
	printf("%c\n",toupper(alpha));
	printf("%c\n",ft_toupper(alpha));
}
*/