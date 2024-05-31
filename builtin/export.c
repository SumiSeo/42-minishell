/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:10 by sumseo            #+#    #+#             */
/*   Updated: 2024/05/31 19:41:48 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_export(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "export";
	while (str[i] && echo[i])
	{
		if (str[i] == echo[i])
			i++;
		else
			return (0);
	}
	if (str[i] == '\0' && echo[i] == '\0')
		return (1);
	return (0);
}
char	*ft_var_strdup(const char *s1)
{
	int		length;
	int		i;
	char	*casted_str;

	length = 0;
	i = 0;
	if (!s1)
		return (NULL);
	while (s1[length])
		length++;
	casted_str = (char *)malloc(sizeof(char) * length + 1);
	if (!casted_str)
		return (NULL);
	while (i < length)
	{
		casted_str[i] = s1[i];
		i++;
	}
	casted_str[i] = '\0';
	return (casted_str);
}

void	func_export(t_parser *cmds, t_envp *env)
{
	char *variable;
	char *value;
	char *new_var;
	int len;
	// int i = 0;

	if (!cmds->str[1])
	{
		// list of exports ? need to check!
		printf("Export arguments dont exits");
		return ;
	}
	variable = ft_strdup(cmds->str[1]);
	value = ft_strdup(cmds->str[2]);

	if (variable[0] != '\0' && value[0] != '\0')
	{
		new_var = ft_strjoin(variable, value);
		len = ft_strlen(new_var);
		push_env(&env, new_var, len);
	}
	else
		return ;
}