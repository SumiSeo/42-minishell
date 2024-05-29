/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 13:29:45 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/18 13:53:11 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
static void	sumi(unsigned int i, char *s)
{
	printf("integer %d\n",i);
	printf("string %s\n", s);
}

int	main(void)
{
	char	*str;

	str = "Sumi is writing code";
	ft_striteri(str,sumi);
}
*/