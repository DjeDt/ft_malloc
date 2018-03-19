/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddinaut <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:39:27 by ddinaut           #+#    #+#             */
/*   Updated: 2018/03/19 19:33:24 by ddinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		check_small_area(void)
{
	size_t	total;

	if (g_page.small == NULL)
	{
		total = TINY_SIZE * getpagesize();
		g_page.small = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_page.small == MAP_FAILED)
		{
			ft_putendl_fd("allocation error. not enought space left.", 2);
			return (ERROR);
		}
		g_page.small->size_used = 0;
		g_page.small->size_max = total;
		g_page.small->map = g_page.small + AREA_SIZE;
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
		total = MEDIUM_SIZE * getpagesize();
		g_page.medium = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		if (g_page.medium == MAP_FAILED)
		{
			ft_putendl_fd("allocation error. not enought space left.", 2);
			return (ERROR);
		}
		g_page.medium->size_used = 0;
		g_page.medium->size_max = total;
		g_page.medium->map = g_page.medium + AREA_SIZE;
		g_page.medium->chunk = NULL;
		g_page.medium->next = NULL;
	}
	return (SUCCESS);
}

int		check_another_area(t_area **area, t_area *prev, size_t size)
{
	size_t	total;

	total = size * getpagesize();
	(*area) = mmap(NULL, total + AREA_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if ((*area) == MAP_FAILED)
	{
		ft_putendl_fd("allocation error. not enought space left.", 2);
		return (ERROR);
	}
	(*area)->size_used = 0;
	(*area)->size_max = total;
	(*area)->map = (*area) + AREA_SIZE;
	(*area)->chunk = NULL;
	(*area)->next = NULL;
	prev->next = (*area);
	return (SUCCESS);
}

int		create_arena(size_t size)
{
	int	ret;

	ret = SUCCESS;
	if (size <= TINY_SIZE)
		ret = check_small_area();
	else if (size <= MEDIUM_SIZE)
		ret = check_medium_area();
	return (ret);
}

void	count_zone(t_area **area)
{
	size_t	count;
	t_area *tmp;

	count = 0;
	tmp = (*area);
	while (tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	ft_putstr("there is ");
	ft_putnbr(count);
	ft_putendl(" area");
}

void	print_all(t_chunk **chunk)
{
	int		count;
	t_chunk *tmp;

	count = 0;
	tmp = (*chunk);
	while (tmp != NULL)
	{
		printf("[chunk %d] size = %zu | statut = %d\n", count, tmp->size, tmp->statut);
		count++;
		tmp = tmp->next;
	}
}

void	print_large(t_area **area)
{
	size_t	count;
	t_area *tmp;

	count = 0;
	tmp = (*area);
	while (tmp != NULL)
	{
		printf("[chunk %zu] : size = %zu\n", count, tmp->size_max);
		count++;
		tmp = tmp->next;
	}
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
	
	if (g_page.small)
		print_all(&g_page.small->chunk);
	if (g_page.medium)
		print_all(&g_page.medium->chunk);
	if (g_page.large)
		print_large(&g_page.large);
	
	return (ret);
}
