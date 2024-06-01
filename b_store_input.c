/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_store_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftanon <ftanon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:59:39 by ftanon            #+#    #+#             */
/*   Updated: 2024/06/01 17:16:53 by ftanon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// Function to take input
int	take_input(t_data *data)
{
	char	*buf;
	int		len;

	buf = readline("💪");
	len = ft_strlen(buf);
	if (len != 0)
	{
		data->input_string = (char *)malloc(sizeof(char) * (len + 1));
		add_history(buf);
		ft_strlcpy(data->input_string, buf, len + 1);
		return (0);
	}
	else
		return (1);
}
