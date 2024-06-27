/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 20:58:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/27 18:11:15 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	take_input(t_data *data, t_env *env_list)
{
	int		size;
	char	cwd[1024];
	char	*pretty_prompt;

	size = 0;
	(void)env_list;
	getcwd(cwd, sizeof(cwd));
	pretty_prompt = ft_strjoin(cwd, ">");
	if (!pretty_prompt)
		return (1);
	data->input = readline(pretty_prompt);
	free(pretty_prompt);
	if (data->input == NULL)
	{
		free_array(data->all_paths);
		free(data);
		// free_env_list(&env_list);
		exit(0);
	}
	if (ft_strlen(data->input) != 0)
	{
		add_history(data->input);
		return (0);
	}
	else
		return (1);
}
