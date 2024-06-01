/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:56:45 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 15:57:25 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_builtin_function(char **array, char *str)
{
	int			i;

	i = 0;
	while (array[i])
	{
		if (ft_strncmp(str, array[i], ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*find_path(char *paths_array, char **array_argv)
{
	char		*joined;
	char		*path;

	joined = ft_strjoin(paths_array, "/");
	path = ft_strjoin(joined, array_argv[0]);
	if (access(path, R_OK) == 0)
	{
		// printf("%s\n", path);
		return (path);
	}
	free(joined);
	free(path);
	return (NULL);
}

void	search_command(t_parse *par_list, t_data *data)
{
	char	*arr[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int		i;

	i = 0;
	while (par_list)
	{
		if (ft_strncmp(par_list->str[0], "/", 1) == 0)
		{
			par_list->path = par_list->str[0];
		}
		else if (is_builtin_function(arr, par_list->str[0]))
		{
			par_list->builtin = 1;
		}
		else
		{
			while (data->str[i])
			{
				par_list->path = find_path(data->str[i], par_list->str);
				if (par_list->path != NULL)
					break;
				// printf("%s\n", par_list->path);
				i++;
			}
		}
		par_list = par_list->next;
	}
}