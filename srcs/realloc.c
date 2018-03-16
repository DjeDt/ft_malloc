/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:56:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/16 19:57:07 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*check_if_enough_space(t_chunk **chunk, size_t size, void *ptr)
{
	/*
	**	check if chunk can extend to size
	**	if not, free() and malloc()
	*/
	size_t	count;
	char	*tmp;

	count = (*chunk)->size;
	tmp = (*chunk)->data;
	while (count < size)
	{
		if ((tmp + count) != '\0')
		{
			free(ptr);
			ptr = malloc(size);
//			ft_memcpy(ptr, (*chunk)->dst);
			return (ptr);
		}
		size++;
	}
	(*chunk)->size = size;
	return ((*chunk)->data);
}

void	*search_in_this_map(t_chunk **chunk, void *ptr, size_t size)
{
	t_chunk *tmp;

	tmp = (*chunk);
	while (tmp != NULL)
	{
		if (tmp->data == ptr)
		{
			ptr = check_if_enough_space(&tmp, size, ptr);
			return (tmp->data);
		}
		tmp = tmp->next;
	}
	return (ptr);
}

void	*search_smaller_ptr(t_area **area, void *ptr, size_t size)
{
	t_area *tmp;

	tmp = (*area);
	if (tmp != NULL)
	{
		search_in_this_map(&tmp->chunk, ptr, size);
		tmp = tmp->next;
	}
	return (ptr);
}

void	*search_large_ptr(t_area **area, void *ptr, size_t size)
{
	t_area *tmp;

	tmp = (*area);
	while (tmp != NULL)
	{
		if (tmp->map == ptr)
		{
			ft_putendl("found large");
			(void)size;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (ptr);
}

void	*search_ptr(void *ptr, size_t size)
{
	t_chunk	*chunk;

	if ((chunk = search_smaller_ptr(&g_page.small, ptr, size)) == NULL)
	{
		if ((chunk = search_smaller_ptr(&g_page.medium, ptr, size)) == NULL)
			chunk = search_large_ptr(&g_page.large, ptr, size);
	}
	return (ptr);
}

void	print_chunk(t_chunk **chunk)
{
	t_chunk *tmp;

	tmp = (*chunk);
	while (tmp != NULL)
	{
		printf("chunk addr = %p\n", tmp);
		printf("chunk size = %zu\n", tmp->size);
		tmp = tmp->next;
	}
	printf("\n[end of print chunk]\n");
}

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		ptr = malloc(size);
	else if (ptr != NULL && size == 0)
	{
		free(ptr);
		ptr = malloc(1);
	}
	else
		ptr = search_ptr(ptr, size);
	print_chunk(&g_page.small->chunk);
	return (ptr);
}
