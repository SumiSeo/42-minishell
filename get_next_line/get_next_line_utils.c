/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:20:55 by ftanon            #+#    #+#             */
/*   Updated: 2024/04/05 15:01:50 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlen(const char *string)
// {
// 	int	i;

// 	i = 0;
// 	while (string[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char	*ft_strdup(const char *source)
// {
// 	char	*destination;
// 	int		i;
// 	size_t	length;

// 	i = 0;
// 	length = ft_strlen(source);
// 	destination = (char *)malloc(length +1);
// 	if (destination == NULL)
// 		return (NULL);
// 	while (source[i] != '\0')
// 	{
// 		destination[i] = source[i];
// 		i++;
// 	}
// 	destination[i] = '\0';
// 	return (destination);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*dest;
// 	int		position;
// 	int		i;

// 	if (s1 == 0 || s2 == 0)
// 		return (0);
// 	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	position = 0;
// 	i = 0;
// 	if (dest == NULL)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 		dest[position++] = s1[i++];
// 	i = 0;
// 	while (s2[i] != '\0')
// 		dest[position++] = s2[i++];
// 	dest[position] = '\0';
// 	return (dest);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*dest;
// 	int		i;
// 	int		malloclength;

// 	malloclength = 0;
// 	i = 0;
// 	if (s == NULL)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 		malloclength = 0;
// 	else if (len > ft_strlen(s) - start + 1)
// 		malloclength = ft_strlen(s) - start;
// 	else
// 		malloclength = len;
// 	dest = (char *)malloc(sizeof(char) * (malloclength +1));
// 	if (dest == NULL)
// 		return (NULL);
// 	while (i < malloclength && s[start] != '\0')
// 	{
// 		dest[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

int	ft_searchchar(const char *string, int searchedChar)
{
	int	i;

	i = 0;
	while (string[i] != '\0' && string[i] != (char)searchedChar)
		i++;
	if (string[i] == '\0' && string[i] != (char)searchedChar)
		return (0);
	return (1);
}
