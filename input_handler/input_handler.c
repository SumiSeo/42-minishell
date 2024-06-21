/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:58:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/21 15:29:39 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_dir(void)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("\033[1;33mminishell😛💻 [%s]\033[0m", cwd);
}
int	take_input(t_data *data)
{
	char	*buf;
	int		len;
	int		size;

	size = 0;
	buf = readline(" ");
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
