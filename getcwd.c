/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:55:37 by ftanon            #+#    #+#             */
/*   Updated: 2024/05/18 15:02:50 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> // for printf

int main(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("pwd: %s\n", pwd);
	return (0);
}
