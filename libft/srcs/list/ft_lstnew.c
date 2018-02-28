/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 16:11:41 by ddinaut           #+#    #+#             */
/*   Updated: 2018/01/18 14:47:08 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ret;
	void	*tmp;

	if (!(ret = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if ((void *)content && content_size > 0)
	{
		if (!(tmp = (void*)malloc(sizeof(void))))
			return (NULL);
		ret->content_size = content_size;
		while (content_size--)
			*(unsigned char *)tmp++ = *(unsigned char *)content++;
		ret->content = tmp - ret->content_size;
	}
	else
	{
		ret->content = NULL;
		ret->content_size = 0;
	}
	ret->next = NULL;
	return (ret);
}
