/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 16:56:42 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/20 18:07:34 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	check if chunk can extend to size
**	if not, free() and malloc()
*/
void	*check_if_enough_space(t_chunk **chunk, size_t size, void *ptr)
{
	t_chunk	*tmp;
	t_chunk	*ret;

	tmp = (*chunk);
	if (tmp->next != NULL)
	{
		if ((ptr + size) < tmp->next->data)
		{
			tmp->size = size;
			return (tmp);
		}
	}
	else
	{
		ret = malloc(size);
		ft_memcpy(ret, ptr, tmp->size);
		free(ptr);
		return (ret);
	}
	return (NULL);
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
	return (NULL);
}

void	*search_smaller_ptr(t_area **area, void *ptr, size_t size)
{
	t_area	*tmp;
	void	*ret;

	ret = NULL;
	tmp = (*area);
	if (tmp != NULL)
	{
		if ((ret = search_in_this_map(&tmp->chunk, ptr, size)) != NULL)
			return (ret);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*search_large_ptr(t_area **area, void *ptr, size_t size)
{
	t_area *tmp;

	tmp = (*area);
	while (tmp != NULL)
	{
		if (tmp->map == ptr)
		{
			free(ptr);
			ptr = malloc(size);
			return (ptr);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	*search_ptr(void *ptr, size_t size)
{
	t_chunk	*chunk;

	if ((chunk = search_smaller_ptr(&g_page.small, ptr, size)) == NULL)
	{
		if ((chunk = search_smaller_ptr(&g_page.medium, ptr, size)) == NULL)
		{
			if ((chunk = search_large_ptr(&g_page.large, ptr, size)) == NULL)
			{
				ptr = malloc(size);
				return (ptr);
			}
		}
	}
	return (chunk->data);
}

void	print_chunk(t_chunk **chunk)
{
	t_chunk *tmp;

	tmp = (*chunk);
	while (tmp != NULL)
	{
		printf("chunk addr = %p\n", tmp);
		printf("chunk statut = %d\n", tmp->statut);
		printf("chunk size = %zu\n", tmp->size);
		tmp = tmp->next;
	}
	printf("\n[end of print chunk]\n");
}

void	*realloc(void *ptr, size_t size)
{
	ft_putstr("[realloc] : ");
	ft_putnbr(size);
	ft_putchar('\n');
	if (ptr == NULL)
		ptr = malloc(size);
	else if (ptr != NULL && size == 0)
	{
		free(ptr);
		ptr = malloc(1);
	}
	else
		ptr = search_ptr(ptr, size);
//	print_chunk(&g_page.small->chunk);
	return (ptr);
}
