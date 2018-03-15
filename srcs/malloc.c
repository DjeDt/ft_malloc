/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/15 16:08:03 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		check_small_area(void)
{
	size_t	total;

	if (g_page.small == NULL)
	{
		total = ((TINY_SIZE * getpagesize()) * 100);
		g_page.small = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_page.small == MAP_FAILED)
		{
			ft_putendl_fd("allocation error. not enought space left.", 2);
			return (ERROR);
		}
		g_page.small->size_used = 0;
		g_page.small->size_max = total;
		g_page.small->map = g_page.small + (sizeof(size_t) * 2);
		g_page.small->chunk = NULL;
		g_page.small->next = NULL;
	}
	return (SUCCESS);
}

int		check_medium_area(void)
{
	size_t	total;

	if (g_page.medium == NULL)
	{
		total = ((MEDIUM_SIZE * getpagesize()) * 100);
		g_page.medium = mmap(NULL, total, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_page.medium == MAP_FAILED)
		{
			ft_putendl_fd("allocation error. not enought space left.", 2);
			return (ERROR);
		}
		g_page.medium->size_used = 0;
		g_page.medium->size_max = total;
		g_page.medium->map = g_page.medium + (sizeof(size_t) * 2);
		g_page.medium->chunk = NULL;
		g_page.medium->next = NULL;
	}
	return (SUCCESS);
}
/*
int		check_large_area(size_t size)
{
	size_t total;
	t_area *save;
	t_area	*prev;

	save = g_page.large;
	while (g_page.large != NULL)
	{
		prev = g_page.large;
		g_page.large = g_page.large->next;
	}
	total = size + (getpagesize() - size % getpagesize());
	g_page.large = mmap(NULL, (total + AREA_SIZE), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_page.large == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (ERROR);
	}
	g_page.large->size_used = 0;
	g_page.large->size_max = size + AREA_SIZE;
	g_page.large->map = g_page.large + (sizeof(size_t) * 2);
	g_page.large->chunk = NULL;
	g_page.large->next = NULL;
	g_page.large = save;
	return (SUCCESS);
}
*/

int		check_small_area2(t_area **area, size_t size)
{
	size_t	total;

	if ((*area) == NULL)
	{
		total = ((size * getpagesize()) * 100);
		(*area) = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if ((*area) == MAP_FAILED)
		{
			ft_putendl_fd("allocation error. not enought space left.", 2);
			return (ERROR);
		}
		(*area)->size_used = 0;
		(*area)->size_max = total;
		(*area)->map = (*area)->map + (sizeof(size_t) * 2);
		(*area)->chunk = NULL;
		(*area)->next = NULL;
	}
	return (SUCCESS);
}

int		create_arena(size_t size)
{
	int	ret;

	ret = 0;
	if (size <= TINY_SIZE)
		ret = check_small_area();
	else if (size <= MEDIUM_SIZE)
		ret = check_medium_area();
	/*
	else
		ret = check_large_area(size);
	*/
	return (ret);
}

void	*malloc(size_t size)
{
	void	*ret;

	if (!size)
		return (NULL);
	ret = NULL;
	if (create_arena(size) != SUCCESS)
		return (NULL);
	ret = push_chunk_to_area(size);
//	ft_putendl("[[PRINT MALLOC CHUNK]]\n");
//	print_allocated_chunk(&g_page.medium->chunk);
//	print_large();
	return (ret);
}
