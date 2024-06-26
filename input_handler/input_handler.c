/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:58:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/26 15:49:11 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	print_dir(void)
// {
// 	printf("\033[1;33mSuminishell😛💻 [%s]\033[0m", cwd);
// 	// printf(">");
// }
int    take_input(t_data *data)
{
	char	*buf;
	int		len;
	int		size;
	char	cwd[1024];
	char	*pretty_prompt;

	size = 0;
	getcwd(cwd, sizeof(cwd));
	pretty_prompt = ft_strjoin(cwd, ">");
	if (!pretty_prompt)
		return (1);
	buf = readline(pretty_prompt);
	free(pretty_prompt);
	if (buf == NULL)
		exit(0);
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
