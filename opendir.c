/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opendir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:17:08 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:21:18 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *entry;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
		return (1);
	}
	if ((dir = opendir(argv[1])) == NULL)
	{
		perror("opendir");
		return (1);
	}
	printf("Contents of directory %s:\n", argv[1]);
	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}
	closedir(dir);
	return (0);
}
