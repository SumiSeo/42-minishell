/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:10:30 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:12:14 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
	struct stat fileStat;
	const char *filePath = "stat_example.txt";

	if (stat(filePath, &fileStat) < 0)
	{
		perror("stat");
		return (1);
	}
	printf("File: %s\n", filePath);
	printf("Size: %ld bytes\n", fileStat.st_size);
	printf("Permissions: %o\n", fileStat.st_mode & 0777);
	printf("Owner UID: %d\n", fileStat.st_uid);
	printf("Owner GID: %d\n", fileStat.st_gid);
	printf("Last modified: %s", ctime(&fileStat.st_mtime));
	return (0);
}