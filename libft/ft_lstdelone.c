/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:44:39 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/21 17:58:45 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
}

/*
static void	del_func(void *p)
{
	printf("deleted %p\n",p);
}

int	main(void)
{
	t_list	l1;

	l1.content ="sumi";
	l1.next= ft_lstnew("seo");
	l1.next->next = ft_lstnew("korean");
	ft_lstdelone(ft_lstnew("sumi"), del_func);
}
*/
