/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:56:15 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:43:16 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*list;

	ret = NULL;
	if (lst && (*f))
	{
		ret = (f)(lst);
		list = ret;
		while (lst->next)
		{
			list->next = (*f)(lst->next);
			list = list->next;
			lst = lst->next;
		}
	}
	return (ret);
}
