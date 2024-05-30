/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:50:48 by ftanon            #+#    #+#             */
/*   Updated: 2024/01/06 13:12:14 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readoneline(int fd)
{
	int		readvalue;
	char	*tempbuffer;
	char	*fulllinebuffer;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	readvalue = 1;
	fulllinebuffer = ft_strdup("");
	while (readvalue > 0)
	{
	readvalue = read(fd, buffer, BUFFER_SIZE);
		if (readvalue > 0)
		{
			buffer[readvalue] = '\0';
			tempbuffer = fulllinebuffer;
			fulllinebuffer = ft_strjoin(tempbuffer, buffer);
			free(tempbuffer);
			if (ft_searchchar(buffer, '\n') == 1)
				readvalue = 0;
		}
	}
	free (buffer);
	return (fulllinebuffer);
}

char	*extractline(char *adjustedbasestring)
{
	int		i;
	char	*printline;

	if (adjustedbasestring == NULL)
		return (NULL);
	i = 0;
	if (adjustedbasestring[i] == '\n')
		printline = ft_substr(adjustedbasestring, 0, 1);
	else
	{
		while (adjustedbasestring[i] != '\n' && adjustedbasestring[i] != '\0')
		i++;
		printline = ft_substr(adjustedbasestring, 0, i + 1);
	}
	return (printline);
}

char	*storestring(char *adjustedbasestring)
{
	int		i;
	int		j;
	char	*storedstring;

	if (adjustedbasestring == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (adjustedbasestring[i] != '\n' && adjustedbasestring[i] != '\0')
		i++;
	while (adjustedbasestring[j] != '\0')
		j++;
	storedstring = ft_substr(adjustedbasestring, i + 1, j - 1 - i);
	if (storedstring[0] == '\0' || j - 1 == i
		|| (adjustedbasestring[0] == '\n' && adjustedbasestring[1] == '\0'))
	{
		free(storedstring);
		return (NULL);
	}
	return (storedstring);
}

char	*get_next_line(int fd)
{
	char		*basestring;
	char		*printline;
	static char	*storedstring;
	char		*adjustedbasestring;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	basestring = readoneline(fd);
	if (basestring == NULL)
		return (NULL);
	if (basestring[0] == '\0' && storedstring == NULL)
		adjustedbasestring = NULL;
	else if (storedstring != NULL && basestring == NULL)
		adjustedbasestring = ft_strdup(storedstring);
	else if (storedstring != NULL && basestring != NULL)
		adjustedbasestring = ft_strjoin(storedstring, basestring);
	else
		adjustedbasestring = ft_strdup(basestring);
	free(storedstring);
	free(basestring);
	printline = extractline(adjustedbasestring);
	storedstring = storestring(adjustedbasestring);
	free(adjustedbasestring);
	return (printline);
}
