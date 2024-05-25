/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:24:18 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/20 11:59:13 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nbtr)
{
	int		i;
	long	nb;
	int		sign;

	sign = 1;
	i = 0;
	nb = 0;
	while ((nbtr[i] >= '\t' && nbtr[i] <= '\r') || nbtr[i] == ' ')
		i++;
	if (nbtr[i] == '-' || nbtr[i] == '+')
	{
		if (nbtr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nbtr[i] >= '0' && nbtr[i] <= '9')
	{
		nb = (nb * 10) + (nbtr[i] - '0');
		i++;
	}
	return (sign * nb);
}
/*
int	main(void)
{
	char	*str = "590310";
	printf("original function ->%d\n",atoi(str));
	printf("my function ->%d\n",ft_atoi(str));

}*/
