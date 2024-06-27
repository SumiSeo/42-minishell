/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:49:28 by sumseo            #+#    #+#             */
/*   Updated: 2024/06/27 19:21:23 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_variable(char s)
{
	if (s == '_' || ft_isalpha(s))
		return (1);
	else
	{
		printf("export : '%c' : not a valid identifier\n", s);
		return (0);
	}
}