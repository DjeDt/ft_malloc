/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:44:26 by ddinaut           #+#    #+#             */
/*   Updated: 2016/11/16 19:36:31 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list **list;
	t_list *nxt;

	list = alst;
	nxt = NULL;
	while (*list)
	{
		del((*list)->content, (*list)->content_size);
		nxt = (*alst)->next;
		free(*list);
		*list = nxt;
	}
}
