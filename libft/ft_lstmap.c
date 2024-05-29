/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:45:03 by sumseo            #+#    #+#             */
/*   Updated: 2023/11/21 15:36:04 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*array;
	t_list	*tmp;

	array = NULL;
	while (lst != NULL)
	{
		tmp = ft_lstnew(f(lst->content));
		if (tmp == NULL)
		{
			while (array)
			{
				tmp = array;
				array = array->next;
				del(tmp->content);
				free(tmp);
			}
		}
		ft_lstadd_back(&array, tmp);
		lst = lst->next;
	}
	return (array);
}
/*
static void	*sumi(void *p)
{
	return (p + 1);
}

static void	del(void *p)
{
	printf("deleted %p\n", p);
}

int	main(void)
{
	t_list	l1;
	t_list	*l2;

	l1.content = "sumi";
	l1.next = ft_lstnew("seo");
	l1.next->next = ft_lstnew("korean");
	l1.next->next->next = ft_lstnew("42");
	l2 = ft_lstmap(&l1, sumi, del);
	while (l2)
	{
		printf("%s\n", (char *)l2->content);
		l2 = l2->next;
	}
	l2 = &l1;
	while (l2)
	{
		printf("%s\n", (char *)l2->content);
		l2 = l2->next;
	}
}
*/
