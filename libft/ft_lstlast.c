/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:44:20 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/21 11:47:58 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list l1;

	l1.content = "first_node";
	t_list *ptr = &l1;
	printf("%s\n", (char *)ptr->content);
	l1.next = ft_lstnew("second_node");
	l1.next->next = ft_lstnew("third");
	ft_lstadd_back(&ptr, ft_lstnew("4th"));
	printf("%s\n", (char *)ft_lstlast(&l1)->content);
	printf("%s\n", (char *)ptr->content);
}*/