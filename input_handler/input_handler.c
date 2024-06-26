/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:58:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/26 16:46:52 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	print_dir(void)
// {
// 	printf("\033[1;33mSuminishell😛💻 [%s]\033[0m", cwd);
// 	// printf(">");
// }
int	take_input(t_data *data, t_env *env_list)
{
	char	*buf;
	int		len;
	int		size;
	char	cwd[1024];

	size = 0;
	data->input = NULL;
	buf = readline(getcwd(cwd, sizeof(cwd)));
	if (buf == NULL)
	{
		free(data);
		free_env_list(&env_list);
		exit(0);
	}
	len = ft_strlen(buf);
	if (len != 0)
	{
		data->input = (char *)malloc(sizeof(char) * (len + 1));
		add_history(buf);
		size = ft_strlcpy(data->input, buf, len + 1);
		return (0);
	}
	else
		return (1);
}
