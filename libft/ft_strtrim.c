/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:01:56 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/16 13:32:06 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_index(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*casted_s1;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = 0;
	end = 0;
	if (!s1)
		return (NULL);
	end = ft_strlen(s1);
	while (ft_get_index(set, s1[start]))
		start++;
	while (end > start && ft_get_index(set, s1[end - 1]))
		end--;
	casted_s1 = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!casted_s1)
		return (NULL);
	while (start < end)
		casted_s1[i++] = s1[start++];
	casted_s1[i] = '\0';
	return (casted_s1);
}

/*
int	main(void)
{
	char	*str;
	char	*set;

	str = "aaaajjjjjjaajkacbaj";
	set = "aj";
	printf("Return value :%s\n", ft_strtrim(str,set));
}

*/
