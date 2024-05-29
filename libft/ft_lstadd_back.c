/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:27:12 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/21 13:31:59 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
/*
int	main(void)
{
	t_list	l1;
	t_list	*ptr;

	l1.content = "first_node";
	ptr = &l1;
	printf("%s\n", (char *)ptr->content);
	l1.next = ft_lstnew("second_node");
	l1.next->next = ft_lstnew("third");
	l1.next->next->next = ft_lstnew("fourth");
	ft_lstadd_back(&ptr, ft_lstnew("5th"));
	//	printf("%s\n", (char *)ft_lstlast(&l1)->content);
	printf("%s\n", (char *)ft_lstlast(&l1)->content);
}
*/