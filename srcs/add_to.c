/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:27:29 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/06 18:30:10 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_chunk		*search_free_chunk(size_t size, t_chunk **list)
{
	t_chunk	*ret;

	if ((*list) == NULL)
		return (NULL);
	ret = (*list);
	while (ret != NULL)
	{
		if (ret->size >= size && ret->statut == FREE)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

t_chunk		*create_chunk(size_t size)
{
	t_chunk *new;

//	size = get_power_of_2(size);
	new = mmap(NULL, size + HEADER_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new == MAP_FAILED)
	{
		ft_putendl_fd("allocation error: no space left", 2);
		return (NULL);
	}
	new->size = size;
	new->statut = USED;
	new->next = NULL;
	return (new);
}

void	*add_to_tiny(size_t size, t_chunk **tiny)
{
	t_chunk	*tmp;

	if ((*tiny) == NULL)	/* in case of first call */
	{
		(*tiny) = create_chunk(size);
		return ((*tiny));
	}
	else
	{
		tmp = (*tiny);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_chunk(size);
	}
	return (tmp->next);
}

void	*add_to_medium(size_t size, t_chunk **medium)
{
	t_chunk	*tmp;

	if ((*medium) == NULL)	/* in case of first call */
	{
		(*medium) = create_chunk(size);
		return (*medium);
	}
	else
	{
		tmp = (*medium);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_chunk(size);
		return (tmp->next);
	}
}

/*
void	*add_to_medium(size_t size, t_chunk **medium)
{
	t_chunk	*tmp;

	tmp = NULL;
	if ((*medium) == NULL) // in case of first call
	{
		(*medium) = create_new_pages(size, MEDIUM_SIZE);
		return (add_to_medium(size, medium));	// medium page isn't NULL anymore
	}
	else
	{
		tmp = (*medium);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_chunk(size);
	}
	return (tmp->next);
}
*/

void	*add_to_large(size_t size, t_chunk **large)
{
	t_chunk	*tmp;

	if ((*large) == NULL)
	{
		(*large) = create_new_pages(size, LARGE_SIZE);
		return (add_to_large(size, large));
	}
	else
	{
		tmp = (*large);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = create_chunk(size);
	}
	return (tmp->next);
}
